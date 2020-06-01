//===--- CastSignednessCheck.cpp - clang-tidy -----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CastSignednessCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsltest {

void CastSignednessCheck::registerMatchers(MatchFinder *Finder) {
  // M5-0-4
  // check cstylecastexpr and castexpr
  // getCastKind -> INtegralCast
  // Finder->addMatcher(implicitCastExpr())
  //       .bind("signcast"), this);
  Finder->addMatcher(
    binaryOperator(isAssignmentOperator())
        .bind("signcast"), this);
}

void CastSignednessCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *Op = Result.Nodes.getNodeAs<BinaryOperator>("signcast");

  auto LHS = Op->getLHS();
  auto RHS = Op->getRHS();

  auto LHSType = LHS->getType();
  auto RHSType = RHS->getType();


  // if (RHSType == CastExpr) {
  //   auto castType = RHSType.QualType;    // getQualType
  //   auto actualType = RHSType->getType();
  //   if (actualType == LHSType && actualType == castType) {  // recast object to its own type...
  //     return;
  //   } 
  //   diag(Op->getOperatorLoc(), "function %0 is insufficiently awesome")
  //     << castType;
  // } else if (RHSType == LHSType) {
  //   return;
  // }
  
  diag(Op->getOperatorLoc(), "function is insufficiently awesome");
  //      << Op;
}

} // namespace bsltest
} // namespace tidy
} // namespace clang
