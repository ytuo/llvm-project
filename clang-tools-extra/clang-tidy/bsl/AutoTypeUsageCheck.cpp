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

AST_MATCHER(ValueDecl, isFundamentalType) {
  return Node.getType().getTypePtr()->isFundamentalType();
}

AST_MATCHER(ParmVarDecl, isTemplate) { return Node.isTemplated(); }

void AutoTypeUsageCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      valueDecl(hasType(autoType()), hasDescendant(cxxStdInitializerListExpr()))
          .bind("list"),
      this);
  
  Finder->addMatcher(valueDecl(hasType(autoType()), isFundamentalType(),
                               unless(has(callExpr())))
                         .bind("decl"),
                     this);

  Finder->addMatcher(
      functionDecl(returns(autoType()),
                   unless(allOf(hasDescendant(parmVarDecl(isTemplate())),
                                hasTrailingReturn())))
          .bind("trail"),
      this);
}

void AutoTypeUsageCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *ListDecl = Result.Nodes.getNodeAs<ValueDecl>("list");
  if (ListDecl)
    diag(ListDecl->getLocation(), "auto cannot be used for list initializers");

  const auto *MatchedDecl = Result.Nodes.getNodeAs<ValueDecl>("decl");
  if (MatchedDecl)
    diag(MatchedDecl->getLocation(),
         "auto cannot be used to declare variable of fundamental type");

  const auto *MatchedTempDecl = Result.Nodes.getNodeAs<FunctionDecl>("trail");
  if (MatchedTempDecl) {
    if (isa<CXXMethodDecl>(MatchedTempDecl)) {
      if (!cast<CXXMethodDecl>(MatchedTempDecl)->isLambdaStaticInvoker())
        diag(MatchedTempDecl->getLocation(),
             "auto can only be used for declaring function templates with a "
             "trailing return");
    } else {
      diag(MatchedTempDecl->getLocation(),
           "auto can only be used for declaring function templates with a "
           "trailing return");
    }
  }
}

} // namespace bsl
} // namespace tidy
} // namespace clang
