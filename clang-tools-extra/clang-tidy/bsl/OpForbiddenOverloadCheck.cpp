//===--- OpForbiddenOverloadCheck.cpp - clang-tidy ------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "OpForbiddenOverloadCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

AST_MATCHER(FunctionDecl, isInstanceMethod) {
  const auto MD = dyn_cast<CXXMethodDecl>(&Node);
  return MD && MD->isInstance();
}

void OpForbiddenOverloadCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(cxxOperatorCallExpr(
                       hasAnyOverloadedOperatorName("&&", "||", ",", "[]")
                     ).bind("op-call"),
                    this);

  Finder->addMatcher(functionDecl(
                       hasOverloadedOperatorName("&"), parameterCountIs(1),
                       unless(isInstanceMethod())
                     ).bind("op-decl-non-instance"),
                     this);

  Finder->addMatcher(cxxMethodDecl(
                       hasOverloadedOperatorName("&"), parameterCountIs(0),
                       isInstanceMethod()
                     ).bind("op-decl-instance"),
                     this);
}

void OpForbiddenOverloadCheck::check(const MatchFinder::MatchResult &Result) {
  const auto Call = Result.Nodes.getNodeAs<CXXOperatorCallExpr>("op-call");

  if (Call) {
    const auto Loc = Call->getOperatorLoc();
    if (Loc.isInvalid())
      return;

    const auto Str = getOperatorSpelling(Call->getOperator());
    diag(Loc, "overloaded operator%0 is forbidden") << Str;

    return;
  }

  const auto FD = Result.Nodes.getNodeAs<FunctionDecl>("op-decl-non-instance");
  if (FD) {
    const auto CFD = FD->getCanonicalDecl();
    if (CFD->getSourceRange().isInvalid())
        return;

    const auto Loc = CFD->getSourceRange().getBegin();
    diag(Loc, "overloaded address-of operator is forbidden");

    return;
  }

  const auto MD = Result.Nodes.getNodeAs<CXXMethodDecl>("op-decl-instance");
  if (MD) {
    const auto CMD = MD->getCanonicalDecl();
    if (CMD->getSourceRange().isInvalid())
      return;

    const auto Loc = CMD->getSourceRange().getBegin();
    diag(Loc, "overloaded address-of operator is forbidden");

    return;
  }
}

} // namespace bsl
} // namespace tidy
} // namespace clang
