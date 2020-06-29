//===--- AutoTypeUsageCheck.cpp - clang-tidy ------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AutoTypeUsageCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void AutoTypeUsageCheck::registerMatchers(MatchFinder *Finder) {
  // var: is return value and has type of function
  // 
  // (1) binaryoperator -> LHS hasType(autoType()) --> vardecl, RHS = callexpr
  // (2) cxxCtorInitializer(unless()) ??? --> binaryoperator -> hasType RHS = not Type isFundamentalType() 
  // (3) lambdaExpr parmVarDecl(hasType(autoType()))
  // (4) functionDecl(hasTrailingReturn()), hasType(autoType())
  Finder->addMatcher(expr(hasType(autoType())).bind("x"), this);
  Finder->addMatcher(valueDecl(hasType(autoType())).bind("decl"), this);
  Finder->addMatcher(classTemplateDecl(hasType(autoType())).bind("temp"), this);  //  functionTemplateDecl

}

void AutoTypeUsageCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  // const auto *MatchedExpr = Result.Nodes.getNodeAs<Expr>("x");
  // if (MatchedExpr)
  //   diag(MatchedExpr->getBeginLoc(), "function is insufficiently awesome");
  const auto *MatchedExpr = Result.Nodes.getNodeAs<Expr>("x");
  if (MatchedExpr)
    diag(MatchedExpr->getBeginLoc(), "function is insufficiently awesome");
  const auto *MatchedDecl = Result.Nodes.getNodeAs<VarDecl>("decl");
  if (MatchedDecl)
    diag(MatchedDecl->getLocation(), "decl is insufficiently awesome");
  const auto *MatchedTempDecl = Result.Nodes.getNodeAs<ClassTemplateDecl>("decl");
  if (MatchedTempDecl)
    diag(MatchedTempDecl->getLocation(), "temp decl is insufficiently awesome");
}

} // namespace bsl
} // namespace tidy
} // namespace clang
