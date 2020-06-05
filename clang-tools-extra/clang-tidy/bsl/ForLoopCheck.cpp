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
  Finder->addMatcher(expr(anyOf(floatLiteral(), expr(hasType(realFloatingPointType()))
    )).bind("float"), this);

  Finder->addMatcher(forStmt(hasIncrement(binaryOperator(hasOperatorName(",")))).bind("singlecounter"), this);

  // Finder->addMatcher(forStmt(anyOf(
  //   hasLoopInit(expr(binaryOperator(hasRHS(floatLiteral())))),
  //   hasLoopInit(declStmt(hasSingleDecl(varDecl(hasType(realFloatingPointType()))))),
  //   hasLoopInit(declStmt(hasSingleDecl(varDecl(hasDescendant(floatLiteral()))))) 
  //   )).bind("floatinit"), this);
  // Finder->addMatcher(forStmt(//anyOf(
  //     // hasIncrement(expr(hasType(realFloatingPointType()))),
  //     hasIncrement(binaryOperator(hasRHS(floatLiteral())))
  //   ).bind("floatcounter"), this);
  // Finder->addMatcher(forStmt(anyOf(
  //     hasCondition(expr(hasType(realFloatingPointType()))),
  //     hasCondition(binaryOperator(hasRHS(floatLiteral())))
  //   )).bind("floatcond"), this);
}

void ForLoopCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *ForIncSingle = Result.Nodes.getNodeAs<ForStmt>("singlecounter");
  if (ForIncSingle) {
      auto locs = ForIncSingle->getInc()->getExprLoc();
      diag(locs, "for loop must have single loop-counter");
  }

  const auto *FloatEx = Result.Nodes.getNodeAs<Expr>("float");
  if (FloatEx) {
      diag(FloatEx->getExprLoc(), "float type not allowed");
  }

  // const auto *ForInitFloat = Result.Nodes.getNodeAs<ForStmt>("floatinit");
  // const auto *ForIncFloat = Result.Nodes.getNodeAs<ForStmt>("floatcounter");
  // const auto *ForCondFloat = Result.Nodes.getNodeAs<ForStmt>("floatcond");
  // SourceLocation locf; 

  // if (ForInitFloat) {
  //     locf = ForInitFloat->getInit()->getBeginLoc();
  //     diag(locf, "for loop counter cannot be of floating point type");
  // } else if (ForIncFloat) {
  //     locf = ForIncFloat->getInc()->getExprLoc();
  //     diag(locf, "for loop counter cannot be of floating point type (increment by float)");
  // } else if (ForCondFloat) {
  //     locf = ForCondFloat->getCond()->getExprLoc();
  //     diag(locf, "for loop counter cannot be of floating point type (comparison to float)");
  // }

}

} // namespace bsl
} // namespace tidy
} // namespace clang
