//===--- DestructorAccessSpecifierCheck.cpp - clang-tidy ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "DestructorAccessSpecifierCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void DestructorAccessSpecifierCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(cxxDestructorDecl( 
                    unless(anyOf(cxxDestructorDecl(isPublic()),
                           cxxDestructorDecl(isPublic(), isOverride()),
                           cxxDestructorDecl(isProtected(), unless(isVirtual()))
                    ))).bind("destructor"), this);

  Finder->addMatcher(cxxDestructorDecl(isPublic(), unless(isVirtual())).bind("nonvirtual"), this);
}

void DestructorAccessSpecifierCheck::check(const MatchFinder::MatchResult &Result) {
  const auto Mgr = Result.SourceManager;
  
  const auto *MatchedDecl = Result.Nodes.getNodeAs<CXXDestructorDecl>("destructor");
  if (MatchedDecl) {
    auto Loc = MatchedDecl->getLocation();
    if (Mgr->getFileID(Loc) != Mgr->getMainFileID())
      return;
    diag(Loc, "base class destructor must be public virtual, public override, or protected non-virtual");
  }

  const auto *VDecl = Result.Nodes.getNodeAs<CXXDestructorDecl>("nonvirtual");
  if (VDecl) {
    auto LocV = VDecl->getLocation();
    if (Mgr->getFileID(LocV) != Mgr->getMainFileID())
      return;
    if (!VDecl->getParent()->isEffectivelyFinal())
      diag(LocV, "if public destructor is nonvirtual, then class must be declared final. Destructor of base class should be public virtual");
  }
  
}

} // namespace bsl
} // namespace tidy
} // namespace clang
