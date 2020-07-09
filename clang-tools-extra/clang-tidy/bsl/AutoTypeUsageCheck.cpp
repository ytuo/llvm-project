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

AST_MATCHER(ParmVarDecl, isTemplate) {   
  // return Node.getReturnType().getTypePtr()->hasAutoForTrailingReturnType();
  return Node.isTemplated();     // isTemplateParameter()
}

void AutoTypeUsageCheck::registerMatchers(MatchFinder *Finder) {

  // Finder->addMatcher(valueDecl(hasType(autoType()), has(initListExpr())).bind("decl"), this);
  Finder->addMatcher(valueDecl(hasType(autoType()), hasDescendant(cxxStdInitializerListExpr())).bind("list"), this);  // ok
  Finder->addMatcher(valueDecl(hasType(autoType()), isFundamentalType(),    // vardecl?
                    unless(has(callExpr()))     // only has? what if 1 + f()
                    ).bind("decl"), this);  // ok, combine with previous

  // Finder->addMatcher(valueDecl(hasType(autoType()), 
  //                   anyOf(hasDescendant(cxxStdInitializerListExpr()), 
  //                     allOf(isFundamentalType(), unless(has(callExpr()))))
  //                   ).bind("decl"), this);    // ok, combined

  // Finder->addMatcher(functionDecl(hasTrailingReturn(), anyOf(hasParent(functionTemplateDecl()), hasParent(classTemplateDecl()))).bind("trail"), this);
  // Finder->addMatcher(functionDecl(isReturnAuto()        // returns(unless(autoType())) // unless(    // isDefinition()
  //         // anyOf(
  //         //   isMethod(),
  //           // allOf(hasTrailingReturn(), 
  //           //   anyOf(hasParent(functionTemplateDecl()), hasParent(classTemplateDecl())))
  //         // )
  //         ).bind("trail"), this);

  // Finder->addMatcher(cxxMethodDecl(unless(hasTrailingReturn())).bind("trail"), this); // parital ok
  // Finder->addMatcher(functionDecl(returns(autoType())).bind("trail"), this);  // ok // returns templateTypeParmType
     // Finder->addMatcher(functionDecl(hasDescendant(declRefExpr(hasType(templateTypeParmType())))).bind("trail"), this);   // ok?
     // Finder->addMatcher(functionDecl(hasDescendant(parmVarDecl(isTemplate()))).bind("trail"), this); // ok
  // Finder->addMatcher(functionDecl(anyOf(returns(autoType()),
  //           allOf(hasTrailingReturn(),
  //           unless(hasDescendant(parmVarDecl(isTemplate())
  //             )))
  //           )).bind("trail"), this); // ok
  Finder->addMatcher(functionDecl(anyOf(returns(autoType()),    // isLambdaStaticInvoker
        allOf(hasTrailingReturn(), 
          unless(anyOf(hasDescendant(parmVarDecl(isTemplate())), 
                hasParent(cxxRecordDecl(isLambda())),  hasParent(functionTemplateDecl())
                 )))) // hasParent(functionTemplateDecl()) ))))

    // hasTrailingReturn(), unless(hasParent(functionTemplateDecl()))
            // allOf(hasTrailingReturn(),
            // unless(hasDescendant(parmVarDecl(isTemplate())  // or TemplateTypeParmDecl
            //   ))
            ).bind("trail"), this); // ok

      // Finder->addMatcher(functionDecl(returns(autoType()), 
      //           unless(allOf(hasDescendant(parmVarDecl(isTemplate())),
      //               hasTrailingReturn()
      //             ))
      //           ).bind("trail"), this); // ok


   // TemplateTypeParmDecl, FunctionTemplateDecl, method has(DeclRefExpr)
  // functionDecl hasTrailingReturn() unless is template

  // template specialization too?

   // inder->addMatcher(classTemplateDecl(has(returnStmt(hasReturnValue(hasType(autoType()))))).bind("temp"), this);  //  functionTemplateDecl

  // friend auto?
}

void AutoTypeUsageCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *ListDecl = Result.Nodes.getNodeAs<ValueDecl>("list");
  if (ListDecl)
    diag(ListDecl->getLocation(), "auto cannot be used for list initializers");

  const auto *MatchedDecl = Result.Nodes.getNodeAs<ValueDecl>("decl");
  if (MatchedDecl)
    diag(MatchedDecl->getLocation(), "auto cannot be used to declare variable of fundamental type");

  const auto *MatchedTempDecl = Result.Nodes.getNodeAs<FunctionDecl>("trail");
  if (MatchedTempDecl) {
    diag(MatchedTempDecl->getLocation(), "auto can only be used for declaring function templates with a trailing return");

  }    
}

} // namespace bsl
} // namespace tidy
} // namespace clang
