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
  // Finder->addMatcher(cxxThisExpr().bind("this"), this);
  Finder->addMatcher(
      varDecl(unless(anyOf(dependentNameType(), hasType(elaboratedType()))),
              hasAncestor(cxxRecordDecl(hasAnyDependentBases())))
          .bind("var"),
      this);

  Finder->addMatcher(
      declRefExpr(hasAncestor(cxxRecordDecl(hasAnyDependentBases())))
          .bind("this"),
      this);
  // memberexpr
}

void DependentBaseNameCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<VarDecl>("var");
  if (MatchedDecl) {
    // if (isa<ElaboratedType>(MatchedDecl->getType())) {
    diag(MatchedDecl->getLocation(),
         "in a class template with a dependent base, any name that may be "
         "found in that dependent base shall be referred to using a "
         "qualified-id or this->.");
  }

  // getBaseTypeIdentifier

  // ok
  const auto *MatchedExpr = Result.Nodes.getNodeAs<DeclRefExpr>("this");
  if (MatchedExpr) {
    if (!MatchedExpr->hasQualifier()) {
      diag(MatchedExpr->getLocation(),
           "in a class template with a dependent base, any name that may be "
           "found in that dependent base shall be referred to using a "
           "qualified-id or this->.");
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
