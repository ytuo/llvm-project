//===--- ForLoopCheck.cpp - clang-tidy ------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ForLoopCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsltest {

void ForLoopCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(forStmt(hasIncrement(binaryOperator(hasOperatorName(",")))).bind("singlecounter"), this);
  Finder->addMatcher(forStmt(hasIncrement(expr(hasType(realFloatingPointType())))).bind("floatcounter"), this);
  // floatLiteral(), and/or match all forStmt() and check if getInc()->getType() is float
}

void ForLoopCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *ForIncSingle = Result.Nodes.getNodeAs<ForStmt>("singlecounter");
  if (ForIncSingle) {
      diag(ForIncSingle->getForLoc(), "For loop must have single loop-counter");
  }

  const auto *ForIncFloat = Result.Nodes.getNodeAs<ForStmt>("floatcounter");
  if (ForIncFloat) {
      diag(ForIncFloat->getForLoc(), "For loop counter cannot be of floating point type");
  }

}

} // namespace bsltest
} // namespace tidy
} // namespace clang
