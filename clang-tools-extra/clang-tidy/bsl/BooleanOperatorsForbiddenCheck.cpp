//===--- BooleanOperatorsForbiddenCheck.cpp - clang-tidy ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "BooleanOperatorsForbiddenCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void BooleanOperatorsForbiddenCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(binaryOperator(hasAnyOperatorName("&&", "||")).bind("op"), this);
}

void BooleanOperatorsForbiddenCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Op = Result.Nodes.getNodeAs<BinaryOperator>("op");
  const auto Loc = Op->getOperatorLoc();

  if (Loc.isInvalid())
    return;

  diag(Loc, "boolean operators && and || are forbidden");
}

} // namespace bsl
} // namespace tidy
} // namespace clang
