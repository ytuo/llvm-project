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

AST_MATCHER(CXXRecordDecl, isPOD) { return Node.isPOD(); }

void NonPodClassdefCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      declaratorDecl(anyOf(fieldDecl(), varDecl()), unless(isPrivate()),
                     hasParent(cxxRecordDecl(isClass(), unless(isPOD()))))
          .bind("private"),
      this);

  Finder->addMatcher(
      cxxRecordDecl(hasDefinition(), unless(isClass())).bind("class"), this);
}

void NonPodClassdefCheck::check(const MatchFinder::MatchResult &Result) {
  // Member data
  auto Var = Result.Nodes.getNodeAs<DeclaratorDecl>("private");
  if (Var) {
    auto Loc = Var->getLocation();
    if (Loc.isInvalid() || Loc.isMacroID())
      return;
    diag(Loc, "non-POD class types should have private member data");
  }

  // Class non-POD type
  auto NonPodClass = Result.Nodes.getNodeAs<CXXRecordDecl>("class");

  if (NonPodClass) {
    auto PodLoc = NonPodClass->getLocation();
    if (PodLoc.isInvalid() || PodLoc.isMacroID())
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