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
//   return Node.isIncrementOp() && Node.isPostfix();
// }

void BitwiseTypeCheck::registerMatchers(MatchFinder *Finder) {
  auto BinaryOps = hasAnyOperatorName("~",
                                      "<<", "<<=");
  Finder->addMatcher(binaryOperator(BinaryOps).bind("op"), this);
}


void BitwiseTypeCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *MatchedDecl = Result.Nodes.getNodeAs<BinaryOperator>("op");

  auto LHS = MatchedDecl->getLHS();
  auto RHS = MatchedDecl->getRHS();

  auto LHSType = LHS->getType();
  auto RHSType = RHS->getType();

  // CastExpr->getType --> check same type, or error
  // Check isUnsignedInteger
  if (LHSType == RHSType) {
    return;
  }

  // MatchedDecl->getOperatorLoc() ?
  diag(MatchedDecl->getLocation(), "function %0 is insufficiently awesome")
      << MatchedDecl;
  // diag(MatchedDecl->getLocation(), "insert 'awesome'", DiagnosticIDs::Note)
  //     << FixItHint::CreateInsertion(MatchedDecl->getLocation(), "awesome_");
}

} // namespace bsltest
} // namespace tidy
} // namespace clang
