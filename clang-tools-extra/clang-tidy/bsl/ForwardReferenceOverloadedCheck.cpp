//===--- ForwardReferenceOverloadedCheck.cpp - clang-tidy -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ForwardReferenceOverloadedCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

AST_MATCHER(FunctionDecl, isCopyOrMove) {
  if (isa<CXXConstructorDecl>(&Node)) {
    return dyn_cast<CXXConstructorDecl>(&Node)->isCopyOrMoveConstructor();
  } else if (isa<CXXMethodDecl>(&Node)) {
    return dyn_cast<CXXMethodDecl>(&Node)->isCopyAssignmentOperator() ||
           dyn_cast<CXXMethodDecl>(&Node)->isMoveAssignmentOperator();
  }
  return false;
}

void ForwardReferenceOverloadedCheck::registerMatchers(MatchFinder *Finder) {
  auto ForwardingReferenceParmMatcher =
      parmVarDecl(
          hasType(qualType(rValueReferenceType(),
                           references(templateTypeParmType(hasDeclaration(
                               templateTypeParmDecl().bind("type-parm-decl")))),
                           unless(references(qualType(isConstQualified()))))))
          .bind("parm-var");
  Finder->addMatcher(ForwardingReferenceParmMatcher, this);

  Finder->addMatcher(
      functionDecl(unless(anyOf(hasAnyParameter(ForwardingReferenceParmMatcher),
                                isDeleted(), isCopyOrMove())))
          .bind("other"),
      this);
}

void ForwardReferenceOverloadedCheck::check(
    const MatchFinder::MatchResult &Result) {
  auto Mgr = Result.SourceManager;

  // Match functions that definitely do not have forwarding references
  const auto *Function = Result.Nodes.getNodeAs<FunctionDecl>("other");

  bool isForwardRef = true;

  const FunctionDecl *FunctionRef;
  if (Function) {
    isForwardRef = false;
    FunctionRef = Function;
  } else {
    const auto *ParmVar = Result.Nodes.getNodeAs<ParmVarDecl>("parm-var");
    const auto *TypeParmDecl =
        Result.Nodes.getNodeAs<TemplateTypeParmDecl>("type-parm-decl");

    isForwardRef = true;

    // Get the FunctionDecl and FunctionTemplateDecl containing the function
    // parameter.
    const auto *FuncForParam =
        dyn_cast<FunctionDecl>(ParmVar->getDeclContext());
    if (!FuncForParam)
      return;
    const FunctionTemplateDecl *FuncTemplate =
        FuncForParam->getDescribedFunctionTemplate();
    if (!FuncTemplate)
      isForwardRef = false;

    // Check that the template type parameter belongs to the same function
    // template as the function parameter of that type. (This implies that type
    // deduction will happen on the type.)
    const TemplateParameterList *Params = FuncTemplate->getTemplateParameters();
    if (!llvm::is_contained(*Params, TypeParmDecl))
      isForwardRef = false;

    FunctionRef = FuncForParam;
  }

  std::string funcname = FunctionRef->getQualifiedNameAsString();

  auto itr = overloadedFunctions.find(funcname);
  if (itr != overloadedFunctions.end()) {
    std::vector<const FunctionDecl *> collision_vec = itr->second;
    for (auto collision : collision_vec) {
      if (collision->getNumParams() == FunctionRef->getNumParams()) {
        unsigned int locnum =
            Mgr->getPresumedLoc(collision->getLocation()).getLine();
        diag(FunctionRef->getLocation(),
             "function %0 overloads function declaration with forwarding "
             "reference on line %1")
            << funcname << locnum;
        break;
      }
    }
    // Nit: only add if no collision, but this will get cleaned up anyway
    overloadedFunctions[funcname].push_back(FunctionRef);
  } else if (isForwardRef) {
    overloadedFunctions[funcname] = {FunctionRef};

    // Check nonForwardRefFunctions for existing violations
    auto nonforward_itr = nonForwardRefFunctions.find(funcname);
    if (nonforward_itr != nonForwardRefFunctions.end()) {
      std::vector<const FunctionDecl *> collision_vec = nonforward_itr->second;
      for (auto collision : collision_vec) {
        if (collision->getNumParams() == FunctionRef->getNumParams()) {
          unsigned int locnum =
              Mgr->getPresumedLoc(FunctionRef->getLocation()).getLine();
          diag(collision->getLocation(),
               "function %0 overloads function declaration with forwarding "
               "reference on line %1")
              << collision->getQualifiedNameAsString() << locnum;
        }
      }
    }
  } else { // Not a forwarding reference; add to nonForwardRef list
    auto nonforward_itr = nonForwardRefFunctions.find(funcname);
    if (nonforward_itr != nonForwardRefFunctions.end()) {
      nonforward_itr->second.push_back(FunctionRef);
    } else {
      nonForwardRefFunctions[funcname] = {FunctionRef};
    }
  }
}

} // namespace bsl
} // namespace tidy
} // namespace clang
