//===--- DependentBaseNameCheck.cpp - clang-tidy --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "DependentBaseNameCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void DependentBaseNameCheck::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  // Finder->addMatcher(cxxRecordDecl().bind("x"), this);
  // Finder->addMatcher(cxxThisExpr().bind("this"), this);
  // Finder->addMatcher(varDecl(unless(hasType(elaboratedType()))).bind("var"), this);
  Finder->addMatcher(varDecl().bind("var"), this);
  // Finder->addMatcher(declRefExpr().bind("this"), this);
  // memberexpr
}

void DependentBaseNameCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  // const auto *MatchedDecl = Result.Nodes.getNodeAs<CXXRecordDecl>("x");
  // if (MatchedDecl && MatchedDecl->hasAnyDependentBases()) {
  //   diag(MatchedDecl->getLocation(), "dependent base");
  // }

  const auto *MatchedDecl = Result.Nodes.getNodeAs<VarDecl>("var");
  if (isa<ElaboratedType>(MatchedDecl->getType())) {
     diag(MatchedDecl->getLocation(), "elaborate ");
  } else {
    // diag(MatchedDecl->getLocation(), "no elaborate ");
  }
  // if (MatchedDecl->getQualifier()) {
  //    diag(MatchedDecl->getLocation(), "qualifier ");
  // } else {
  //   diag(MatchedDecl->getLocation(), "no qualifier %0 ");
  // }
  // if (MatchedDecl->getType()->hasQualifier()) {
  //    diag(MatchedDecl->getLocation(), "qualifier ");
  // }
  // diag(MatchedDecl->getLocation(), "no qualifier %0 ");

  // const auto *MatchedExpr = Result.Nodes.getNodeAs<DeclRefExpr>("this");
  // if (!MatchedExpr->hasQualifier()) {
  //    diag(MatchedExpr->getLocation(), "no qualifier");
  // }  // ok

  // getBaseTypeIdentifier

  // const auto *MatchedExpr = Result.Nodes.getNodeAs<CXXThisExpr>("this");
  // if (MatchedExpr) {
  //   diag(MatchedExpr->getLocation(), "this");
  //   if (!MatchedExpr->isImplicit()) {
  //     diag(MatchedExpr->getLocation(), "not implicit");
  //   }
  // }
  
}

} // namespace bsl
} // namespace tidy
} // namespace clang
