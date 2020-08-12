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

AST_MATCHER(CXXRecordDecl, hasAnyDependentBases) {
  return Node.hasAnyDependentBases();
}

AST_MATCHER(VarDecl, dependentNameType) {
  return isa<DependentNameType>(Node.getType());
}

void DependentBaseNameCheck::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  // Finder->addMatcher(cxxRecordDecl().bind("x"), this);
  // Finder->addMatcher(cxxThisExpr().bind("this"), this);
  // Finder->addMatcher(varDecl(unless(hasType(elaboratedType()))).bind("var"), this);
  // Finder->addMatcher(varDecl(hasAncestor(cxxRecordDecl(hasAnyDependentBases()))).bind("var"), this);
    Finder->addMatcher(varDecl(unless(anyOf(dependentNameType(), hasType(elaboratedType()))),
                                hasAncestor(cxxRecordDecl(hasAnyDependentBases()))).bind("var"), this);

  Finder->addMatcher(declRefExpr(hasAncestor(cxxRecordDecl(hasAnyDependentBases()))).bind("this"), this);
  // memberexpr
  // normal var
}

void DependentBaseNameCheck::check(const MatchFinder::MatchResult &Result) {
  // const auto *MatchedDecl = Result.Nodes.getNodeAs<CXXRecordDecl>("x");
  // if (MatchedDecl && MatchedDecl->hasAnyDependentBases()) {
  //   diag(MatchedDecl->getLocation(), "dependent base");
  // }

  const auto *MatchedDecl = Result.Nodes.getNodeAs<VarDecl>("var");
  if (MatchedDecl) {
    // if (isa<ElaboratedType>(MatchedDecl->getType())) {
       diag(MatchedDecl->getLocation(), "yar ");
    // } else {
    //   diag(MatchedDecl->getLocation(), "no elaborate %0");
    // }

    // check qualified dependent type ? 
    // QualType declType = MatchedDecl->getType();
    // auto desugar =  MatchedDecl->getType()->getUnqualifiedDesugaredType()->getTypeClassName();
    // bool qual = declType->isInstantiationDependentType();

    // //if (dyn_cast<QualType>(MatchedDecl->getTypeSourceInfo()->getType())->hasQualifiers()) {
    // diag(MatchedDecl->getLocation(), "no elaborate %0 %1 %2") << desugar;
    // if(MatchedDecl->getTypeSourceInfo()) {
    //   diag(MatchedDecl->getLocation(), "elaborate ");
    // } else {
    //   diag(MatchedDecl->getLocation(), "no elaborate %0");
    // }
    // if (MatchedDecl->getQualifier()) {
    //    diag(MatchedDecl->getLocation(), "qualifier ");
    // } else {
    //   diag(MatchedDecl->getLocation(), "no qualifier %0 ");
    // }
    // if (MatchedDecl->getType()->hasQualifier()) {
    //    diag(MatchedDecl->getLocation(), "qualifier ");
    // }
    // diag(MatchedDecl->getLocation(), "no qualifier %0 ");
  }
  
  // getBaseTypeIdentifier

  // ok
  const auto *MatchedExpr = Result.Nodes.getNodeAs<DeclRefExpr>("this");
  if (MatchedExpr) {
    if (!MatchedExpr->hasQualifier()) {
       diag(MatchedExpr->getLocation(), "no qualifier");
    } // else if (has this expr is not implicit) 
    else {
      // diag(MatchedExpr->getLocation(), "has qualifier");
    }
  }
    

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
