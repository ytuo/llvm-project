//===--- IdentifierHideOuterScopeCheck.cpp - clang-tidy -------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "IdentifierHideOuterScopeCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

AST_MATCHER(VarDecl, isCXXClassMember) { return Node.isCXXClassMember(); }

void IdentifierHideOuterScopeCheck::registerMatchers(MatchFinder *Finder) {
  
  Finder->addMatcher(varDecl().bind("x"), this);
  // Finder->addMatcher(varDecl(unless(isCXXClassMember())).bind("x"), this);
}

void IdentifierHideOuterScopeCheck::check(const MatchFinder::MatchResult &Result) {
  auto *D = Result.Nodes.getNodeAs<VarDecl>("x");

  std::string name = D->getNameAsString();
  auto dname = D->getDeclName();  //DeclarationName dname
  const DeclContext *ns = D->getDeclContext();
  auto *curns = ns->getLexicalParent();

  while (curns) {
    // containsDecl()
    for (NamedDecl *item : curns->lookup(dname)) {
      // unless namespace unnamed? 
      if (item->getQualifiedNameAsString() == D->getQualifiedNameAsString()) {
        diag(D->getLocation(), "function previous %0") << item->getName();
      }
    }
    curns = curns->getLexicalParent();
    // LookupParent, Parent

    // how to check if declcontext is class? 
  }

  // auto prev = MatchedDecl->getPreviousDeclImpl();
  // auto prev = MatchedDecl->getPreviousDecl();
  // auto prev = MatchedDecl->getNextRedeclarationImpl();

  // if (prev) {
  //   diag(MatchedDecl->getLocation(), "function previous %0")
  //     << prev->getName();
  // }

  // auto It = MatchedDecl->redecls_begin();
  // auto EndIt = MatchedDecl->redecls_end();
  // for (const VarDecl *VD : MatchedDecl->redecls()) {
  //     diag(MatchedDecl->getLocation(), "%0 %1") << VD->getName() << VD->getDeclContext()->getEnclosingNamespaceContext();
  // }

  // if (It == EndIt) {
  //   diag(MatchedDecl->getLocation(), "no");
  // } else {
  //  diag(MatchedDecl->getLocation(), "yes"); 
  // }
  
}

} // namespace bsl
} // namespace tidy
} // namespace clang
