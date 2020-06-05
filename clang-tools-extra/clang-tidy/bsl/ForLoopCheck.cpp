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
namespace bsl {

void ForLoopCheck::registerMatchers(MatchFinder *Finder) {
  // A6-5-2
  Finder->addMatcher(forStmt(hasIncrement(binaryOperator(hasOperatorName(",")))).bind("singlecounter"), this);
  // forStmt(hasLoopInit(declStmt(hasSingleDecl(varDecl(
  //  hasInitializer(integerLiteral(equals(0)))))))).bind("forLoop");
  Finder->addMatcher(forStmt(anyOf(
      hasLoopInit(expr(hasType(realFloatingPointType()))),
      hasLoopInit(binaryOperator(hasRHS(floatLiteral())))
    )).bind("floatinit"), this);
  Finder->addMatcher(forStmt(anyOf(
      hasIncrement(expr(hasType(realFloatingPointType()))),
      hasIncrement(binaryOperator(hasRHS(floatLiteral())))
    )).bind("floatcounter"), this);
  Finder->addMatcher(forStmt(anyOf(
      hasCondition(expr(hasType(realFloatingPointType()))),
      hasCondition(binaryOperator(hasRHS(floatLiteral())))
    )).bind("floatcond"), this);
}

void ForLoopCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *ForIncSingle = Result.Nodes.getNodeAs<ForStmt>("singlecounter");
  if (ForIncSingle) {
      auto locs = ForIncSingle->getInc()->getExprLoc();
      diag(locs, "for loop must have single loop-counter");
      // diag(ForIncSingle->getForLoc(), "For loop must have single loop-counter");
  }

  const auto *ForInitFloat = Result.Nodes.getNodeAs<ForStmt>("floatinit");
  const auto *ForIncFloat = Result.Nodes.getNodeAs<ForStmt>("floatcounter");
  const auto *ForCondFloat = Result.Nodes.getNodeAs<ForStmt>("floatcond");
  // auto locf = ForIncFloat->getInc()->getRHS()->getExprLoc();
  // get conditional variable
  SourceLocation locf; 
  if (ForInitFloat) {
      locf = ForInitFloat->getInit()->getBeginLoc();
      diag(locf, "for loop counter cannot be of floating point type");
  } else if (ForIncFloat) {
      // locf = ForIncFloat->getInc()->getExprLoc();
      locf = ForIncFloat->getInit()->getBeginLoc();
      diag(locf, "for loop counter cannot be of floating point type (increment by float)");
      // diag(ForIncFloat->getForLoc(), "For loop counter cannot be of floating point type");
  } else if (ForCondFloat) {
      locf = ForCondFloat->getCond()->getExprLoc();
      diag(locf, "for loop counter cannot be of floating point type (comparison to float)");
  }

}

} // namespace bsl
} // namespace tidy
} // namespace clang
