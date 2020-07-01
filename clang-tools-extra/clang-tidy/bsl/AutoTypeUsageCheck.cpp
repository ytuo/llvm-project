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

// AST_MATCHER(CXXMethodDecl, isTemplate) {
//   return Node.getParent() == FunctionDecl::TK_FunctionTemplate;
// }

AST_MATCHER(ValueDecl, isFundamentalType) {
  return Node.getType().getTypePtr()->isFundamentalType();
}


AST_MATCHER(FunctionDecl, isMethod) {   // works
  return Node.getDeclKind() == Decl::CXXMethod;
}

AST_MATCHER(FunctionDecl, isReturnAuto) {   
  // return Node.getReturnType().getTypePtr()->hasAutoForTrailingReturnType();
  return Node.getReturnType().getTypePtr()->getContainedAutoType();
}


void AutoTypeUsageCheck::registerMatchers(MatchFinder *Finder) {
  // var: is return value and has type of function
  // 
  // (1) binaryoperator -> LHS hasType(autoType()) --> vardecl, RHS = callexpr
  // (2) cxxCtorInitializer(unless()) ??? --> binaryoperator -> hasType RHS = not Type isFundamentalType() 
  // (3) lambdaExpr parmVarDecl(hasType(autoType()))
  // (4) functionDecl(hasTrailingReturn()), hasType(autoType())
  // Finder->addMatcher(expr(hasType(autoType())).bind("x"), this);   // not needed
  // Finder->addMatcher(valueDecl(hasType(autoType())    // vardecl?
  //                   // unless(valueDecl(ignoringImpCasts(hasType(autoType())))
  //                   ).bind("decl"), this); 

  // Finder->addMatcher(valueDecl(hasType(autoType()), isFundamentalType(),    // vardecl?
  //                   unless(has(callExpr()))     // only has? what if 1 + f()
  //                   ).bind("decl"), this);  // ok?

  // Finder->addMatcher(functionDecl(hasTrailingReturn(), anyOf(hasParent(functionTemplateDecl()), hasParent(classTemplateDecl()))).bind("trail"), this);
  // Finder->addMatcher(functionDecl(isReturnAuto()        // returns(unless(autoType())) // unless(    // isDefinition()
  //         // anyOf(
  //         //   isMethod(),
  //           // allOf(hasTrailingReturn(), 
  //           //   anyOf(hasParent(functionTemplateDecl()), hasParent(classTemplateDecl())))
  //         // )
  //         ).bind("trail"), this);

  // Finder->addMatcher(cxxMethodDecl(unless(hasTrailingReturn())).bind("trail"), this); // parital ok
    Finder->addMatcher(cxxMethodDecl().bind("trail"), this);  // ok ish

  // template specialization too?

   // inder->addMatcher(classTemplateDecl(has(returnStmt(hasReturnValue(hasType(autoType()))))).bind("temp"), this);  //  functionTemplateDecl

  // friend auto?
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

  // const auto *MatchedTempDecl = Result.Nodes.getNodeAs<FunctionDecl>("trail");
  // if (MatchedTempDecl)
  //   diag(MatchedTempDecl->getLocation(), "temp decl is insufficiently awesome");

  const auto *MatchedClassDecl = Result.Nodes.getNodeAs<CXXMethodDecl>("trail");
  
  if (MatchedClassDecl) {
    diag(MatchedClassDecl->getLocation(), "temp decl is insufficiently derp ");
    const auto *MatchedClassDecl2 = MatchedClassDecl->getParent();
    
    if (MatchedClassDecl2->getDescribedClassTemplate()->isThisDeclarationADefinition()) {   // does this do anything
      diag(MatchedClassDecl->getLocation(), "bleh ");
    }
    if (MatchedClassDecl->getTemplatedKind() == FunctionDecl::TK_NonTemplate)
      diag(MatchedClassDecl->getLocation(), "temp decl is insufficiently 1 ");
    if (MatchedClassDecl->getTemplatedKind() == FunctionDecl::TK_MemberSpecialization)
      diag(MatchedClassDecl->getLocation(), "temp decl is insufficiently 2 ");
    if (MatchedClassDecl->getTemplatedKind() == FunctionDecl::TK_FunctionTemplateSpecialization)
      diag(MatchedClassDecl->getLocation(), "temp decl is insufficiently 3 ");
    if (MatchedClassDecl->getTemplatedKind() == FunctionDecl::TK_FunctionTemplate)
      diag(MatchedClassDecl->getLocation(), "temp decl is insufficiently 4 ");
    if (MatchedClassDecl->getTemplatedKind() == FunctionDecl::TK_DependentFunctionTemplateSpecialization)
      diag(MatchedClassDecl->getLocation(), "temp decl is insufficiently 5 ");
  }
    
}

} // namespace bsl
} // namespace tidy
} // namespace clang
