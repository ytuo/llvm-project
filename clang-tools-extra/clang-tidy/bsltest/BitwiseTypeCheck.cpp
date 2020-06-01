//===--- BitwiseTypeCheck.cpp - clang-tidy --------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "BitwiseTypeCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsltest {

// AST_MATCHER(BinaryOperator, isBitwiseOp) {
//   return Node.isIncrementOp() && Node.isPostfix(); xx
// }

// BinaryOperator, UnaryOperator) hasParent(ParenExpr)
// AST_MATCHER(ParenExpr) {
//   // check sign?
//   int width = getIntWidth(Node.getSubExpr().getType()) 
//   if width == 8 || width == 16
//   return Node.isIncrementOp() && Node.isPostfix();
// }

void BitwiseTypeCheck::registerMatchers(MatchFinder *Finder) {
  // M5-0-10
  // if parenexpr, if 8bit/16bit (unsigned?), must contain explicit castexpr
  // or must exist explicit castexpr on parenexpr (??)
  // parenexpr not in multiple expressions? (dumb but can happen). Also, makes this a two-step fix
  Finder->addMatcher(expr(anyOf(
                    binaryOperator(hasParent(parenExpr())), 
                    unaryOperator(hasParent(parenExpr()))
                  )).bind("shift"), this);
  // auto BinaryOps = hasAnyOperatorName("<<", "<<=");
  // Finder->addMatcher(binaryOperator(BinaryOps).bind("shift"), this);

  // // https://clang.llvm.org/doxygen/classclang_1_1CharacterLiteral.html signed char?
  // Finder->addMatcher(
  //     unaryOperator(hasOperatorName("~"), hasUnaryOperand(hasType(isUnsignedInteger())))  // unsigned char?
  //         .bind("not"),
  //     this);
}


void BitwiseTypeCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  /* check for right shift binaryoperator or ~ unaryoperator
  binary: get both sides; if left side is a variable, check type
  if unsigned char or short, CastExpr: make sure not implicit
  if right side is expression, decompose and repeat (don't need to do this?)
  */
  const auto *Op = Result.Nodes.getNodeAs<BinaryOperator>("shift");

  auto LHS = Op->getLHS();
  auto RHS = Op->getRHS();

  auto LHSType = LHS->getType();
  auto RHSType = RHS->getType();

  // auto lwidth = getIntWidth(LHSType); 
  // auto rwidth = getIntWidth(RHSType); 
  // // CastExpr->getType --> check same type, or error, isUnsignedInteger
  // // Check isUnsignedInteger
  // if (lwidth == 8 || lwidth == 16 || rwidth == 8 || rwidth == 16) {
  //     diag(Op->getOperatorLoc(), "function is insufficiently awesome");
  // }

  // MatchedDecl->getOperatorLoc() ?
  diag(Op->getOperatorLoc(), "function is insufficiently awesome");
      //<< Op;
  // diag(MatchedDecl->getLocation(), "insert 'awesome'", DiagnosticIDs::Note)
  //     << FixItHint::CreateInsertion(MatchedDecl->getLocation(), "awesome_");
}

} // namespace bsltest
} // namespace tidy
} // namespace clang
