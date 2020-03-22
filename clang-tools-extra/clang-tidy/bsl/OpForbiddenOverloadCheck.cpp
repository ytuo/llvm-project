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

void OpForbiddenOverloadCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
    callExpr(anyOf(
      cxxOperatorCallExpr(hasAnyOverloadedOperatorName("&&", "||", ",", "[]")),
      cxxOperatorCallExpr(
          hasOverloadedOperatorName("&"),
          unless(argumentCountIs(2))
      )
    )).bind("op-call"),
    this);
}

void OpForbiddenOverloadCheck::check(const MatchFinder::MatchResult &Result) {
  const auto Call = Result.Nodes.getNodeAs<CXXOperatorCallExpr>("op-call");

  const auto Loc = Call->getOperatorLoc();
  if (Loc.isInvalid())
    return;

  const auto Mgr = Result.SourceManager;
  if (Mgr->getFileID(Loc) != Mgr->getMainFileID())
    return;

  const auto Str = getOperatorSpelling(Call->getOperator());

  diag(Loc, "overloaded operator%0 is forbidden") << Str;
}

} // namespace bsl
} // namespace tidy
} // namespace clang
