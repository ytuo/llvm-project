//===--- FunctionNameUseCheck.cpp - clang-tidy ----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "FunctionNameUseCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void FunctionNameUseCheck::registerMatchers(MatchFinder *Finder) {
  // This matches any use of a function name that isn't used
  // either with the address-of operator or in a call expression.
  Finder->addMatcher(
    expr(
      declRefExpr(to(functionDecl())),
      unless(hasParent(unaryOperator(hasOperatorName("&")))),
      unless(hasParent(implicitCastExpr(hasParent(callExpr()))))
    ).bind("ref"),
    this);

  // This matches any use of a function name as an argument to a
  // function call (this case is not matched by the matcher above).
  Finder->addMatcher(
    callExpr(hasAnyArgument(
      ignoringImpCasts(declRefExpr(to(functionDecl())).bind("arg"))
    )),
    this);
}

void FunctionNameUseCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Arg = Result.Nodes.getNodeAs<DeclRefExpr>("arg");
  if (Arg) {
    const auto Loc = Arg->getBeginLoc();
    if (Loc.isInvalid())
      return;

    auto D = Arg->getFoundDecl();

    auto Diag =
      diag(Loc, "function name '%0' must be used in call or addressof"
                " expression") << D->getName();
    Diag <<
      FixItHint::CreateInsertion(Loc, Twine("&").str());

    return;
  }

  const auto *Ref = Result.Nodes.getNodeAs<DeclRefExpr>("ref");
  if (Ref) {
    const auto Loc = Ref->getBeginLoc();
    if (Loc.isInvalid())
      return;

    auto D = Ref->getFoundDecl();

    auto Diag =
      diag(Loc, "function name '%0' must be used in call or addressof"
                " expression") << D->getName();
    Diag <<
      FixItHint::CreateInsertion(Loc, Twine("&").str());

    return;
  }
}

} // namespace bsl
} // namespace tidy
} // namespace clang
