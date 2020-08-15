//===--- FunctionNoexceptCheck.cpp - clang-tidy ---------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "FunctionNoexceptCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

AST_MATCHER(FunctionDecl, noExceptSpec) {
  auto ExceptType = Node.getExceptionSpecType();
  return ExceptType == EST_BasicNoexcept || ExceptType == EST_NoexceptFalse ||
         ExceptType == EST_Unevaluated || ExceptType == EST_DependentNoexcept ||
         ExceptType == EST_NoexceptTrue;
}

void FunctionNoexceptCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(functionDecl(unless(anyOf(noExceptSpec(), isImplicit())))
                         .bind("noexcept"),
                     this);
}

void FunctionNoexceptCheck::check(const MatchFinder::MatchResult &Result) {
  const auto Mgr = Result.SourceManager;

  const auto *MatchedDecl = Result.Nodes.getNodeAs<FunctionDecl>("noexcept");
  if (MatchedDecl) {
    auto Loc = MatchedDecl->getLocation();
    if (Mgr->getFileID(Loc) != Mgr->getMainFileID())
      return;
    diag(Loc, "Every function should be marked as noexcept or noexcept(false)");
  }
}

} // namespace bsl
} // namespace tidy
} // namespace clang
