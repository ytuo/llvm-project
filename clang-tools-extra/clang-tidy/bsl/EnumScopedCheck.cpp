//===--- EnumScopedCheck.cpp - clang-tidy --------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "EnumScopedCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void EnumScopedCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(enumDecl().bind("enum"), this);
}

void EnumScopedCheck::check(const MatchFinder::MatchResult &Result) {
  auto Enum = Result.Nodes.getNodeAs<EnumDecl>("enum");

  auto Loc = Enum->getLocation();
  if (Loc.isInvalid() || Loc.isMacroID())
    return;

  auto Mgr = Result.SourceManager;
  if (Mgr->getFileID(Loc) != Mgr->getMainFileID())
    return;

  if (Enum->isScopedUsingClassTag())
    return;

  diag(Loc, "enum declaration is not scoped with 'class' keyword");
}

} // namespace bsl
} // namespace tidy
} // namespace clang
