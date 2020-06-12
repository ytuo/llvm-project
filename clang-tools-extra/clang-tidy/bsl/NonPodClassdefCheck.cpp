//===--- NonPodClassdefCheck.cpp - clang-tidy -----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NonPodClassdefCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void NonPodClassdefCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(cxxRecordDecl(has(accessSpecDecl(anyOf(isPublic(), isProtected())))).bind("private"), this); 
  // Finder->addMatcher(fieldDecl(unless(isPrivate())).bind("private"), this);

  Finder->addMatcher(cxxRecordDecl(hasDefinition(), unless(isClass())).bind("class"), this);

}

void NonPodClassdefCheck::check(const MatchFinder::MatchResult &Result) {
  // member data
  auto Var = Result.Nodes.getNodeAs<CXXRecordDecl>("private");
  if (Var) {
    auto Loc = Var->getLocation();
    if (Loc.isInvalid() || Loc.isMacroID())
      return;

    auto Mgr = Result.SourceManager;
    if (Mgr->getFileID(Loc) != Mgr->getMainFileID())
      return;

    if (Var->isPOD())
      return;
    else
      diag(Loc, "non-POD class types should have private member data");
  }

  // class non-POD type
  auto NonPodClass = Result.Nodes.getNodeAs<CXXRecordDecl>("class");

  if (NonPodClass) {
    auto PodLoc = NonPodClass->getLocation();
    if (PodLoc.isInvalid() || PodLoc.isMacroID())
      return;

    auto Mgr = Result.SourceManager;
    if (Mgr->getFileID(PodLoc) != Mgr->getMainFileID())
      return;

    if (NonPodClass->isPOD())
      return;
    else
      diag(PodLoc, "non-POD type should be defined as a class");
  }

}

} // namespace bsl
} // namespace tidy
} // namespace clang
