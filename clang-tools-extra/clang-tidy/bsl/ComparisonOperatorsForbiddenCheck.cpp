//===--- ComparisonOperatorsForbiddenCheck.cpp - clang-tidy ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ComparisonOperatorsForbiddenCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void ComparisonOperatorsForbiddenCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(binaryOperator(hasAnyOperatorName(">=", "<=")).bind("op"), this);
}

void ComparisonOperatorsForbiddenCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Op = Result.Nodes.getNodeAs<BinaryOperator>("op");
  const auto Loc = Op->getOperatorLoc();

  if (Loc.isInvalid())
    return;

  diag(Loc, "comparison operators >= and <= are forbidden");
}

} // namespace bsl
} // namespace tidy
} // namespace clang
