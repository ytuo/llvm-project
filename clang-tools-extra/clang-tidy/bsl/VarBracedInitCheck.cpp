//===--- VarBracedInitCheck.cpp - clang-tidy ------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "VarBracedInitCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

AST_MATCHER(VarDecl, hasListInitStyle) {
  return Node.getInitStyle() == VarDecl::InitializationStyle::ListInit;
}

void VarBracedInitCheck::registerMatchers(MatchFinder *Finder) {
  // TODO: deal with classes with std::initializer_list ctors
  Finder->addMatcher(
    varDecl(hasInitializer(expr()),
            unless(hasType(autoType())),
            unless(hasListInitStyle())).bind("nonauto-var"),
    this);

  Finder->addMatcher(
    varDecl(hasInitializer(anyOf(initListExpr(), exprWithCleanups())),
            hasType(autoType())).bind("auto-var"),
    this);
}

void VarBracedInitCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *NonAuto = Result.Nodes.getNodeAs<VarDecl>("nonauto-var");

  if (NonAuto) {
    const auto Loc = NonAuto->getLocation();
    if (Loc.isInvalid())
      return;

    const auto Mgr = Result.SourceManager;
    if (Mgr->getFileID(Loc) != Mgr->getMainFileID())
      return;

    diag(Loc, "variable is not initialized via direct list initialization");
    return;
  }

  const auto *Auto = Result.Nodes.getNodeAs<VarDecl>("auto-var");
  if (Auto) {
    const auto Loc = Auto->getLocation();
    if (Loc.isInvalid())
      return;

    const auto Mgr = Result.SourceManager;
    if (Mgr->getFileID(Loc) != Mgr->getMainFileID())
      return;

    const auto Cleanups = dyn_cast<ExprWithCleanups>(Auto->getInit());
    if (Cleanups) {
      if (isa<CXXStdInitializerListExpr>(*Cleanups->children().begin()))
        diag(Loc, "variable declared 'auto' is initialized via list initialization");
    } else {
      diag(Loc, "variable declared 'auto' is initialized via list initialization");
    }

    return;
  }
}

} // namespace bsl
} // namespace tidy
} // namespace clang
