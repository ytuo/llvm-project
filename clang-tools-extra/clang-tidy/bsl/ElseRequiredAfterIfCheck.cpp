//===--- ElseRequiredAfterIfCheck.cpp - clang-tidy ------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ElseRequiredAfterIfCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

#include <iostream>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void ElseRequiredAfterIfCheck::registerMatchers(MatchFinder *Finder) {
  const auto InterruptsControlFlow =
    stmt(
      anyOf(
        returnStmt(),
        continueStmt(),
        breakStmt()
      )
    );

  Finder->addMatcher(
    compoundStmt(
      forEach(
        ifStmt(
          hasThen(
            stmt(
              unless(
                anyOf(
                  InterruptsControlFlow,
                  compoundStmt(has(InterruptsControlFlow))
                )
              )
            )
          ),
          unless(hasElse(stmt())),
          unless(isConstexpr())
        ).bind("if_missing_else")
      )
    ),
    this);

  Finder->addMatcher(
    compoundStmt(
      forEach(
        ifStmt(
          hasThen(
            stmt(
              anyOf(
                InterruptsControlFlow,
                compoundStmt(has(InterruptsControlFlow))
              )
            )
          ),
          hasParent(stmt().bind("parent")),
          unless(hasElse(stmt())),
          unless(isConstexpr())
        ).bind("if_missing_else_next_line")
      )
    ),
    this);

  Finder->addMatcher(
    compoundStmt(
      forEach(
        ifStmt(
          hasThen(
            stmt(
              anyOf(
                InterruptsControlFlow,
                compoundStmt(has(InterruptsControlFlow))
              )
            )
          ),
          hasElse(stmt().bind("unneeded_else")),
          unless(isConstexpr())
        )
      )
    ),
    this
  );
}

void ElseRequiredAfterIfCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *IfMissingElse = Result.Nodes.getNodeAs<IfStmt>("if_missing_else");
  const auto *IfMissingElseNextLine = Result.Nodes.getNodeAs<IfStmt>("if_missing_else_next_line");
  const auto *UnneededElse = Result.Nodes.getNodeAs<Stmt>("unneeded_else");

  if (IfMissingElse) {
    diag(IfMissingElse->getIfLoc(), "'else' is required after 'if'");
  }

  if (IfMissingElseNextLine) {
    auto *Parent = Result.Nodes.getNodeAs<Stmt>("parent");
    for (auto Iter = Parent->child_begin(); Iter != Parent->child_end(); ++Iter) {
      auto next = Iter;
      ++next;
      if (next == Parent->child_end() && *Iter == IfMissingElseNextLine) {
        diag(IfMissingElseNextLine->getIfLoc(), "'else' is required after 'if' or add bsl::touch() after `if`");
      }
    }
  }

  if (UnneededElse && UnneededElse->getBeginLoc().isValid())
    diag(UnneededElse->getBeginLoc(), "do not use 'else' after 'return/continue/break'");
}

} // namespace bsl
} // namespace tidy
} // namespace clang
