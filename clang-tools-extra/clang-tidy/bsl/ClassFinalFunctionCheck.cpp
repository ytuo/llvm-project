//===--- ClassFinalFunctionCheck.cpp - clang-tidy -------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ClassFinalFunctionCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

AST_MATCHER(CXXMethodDecl, isUserProvided) {
  return Node.isUserProvided();
}

void ClassFinalFunctionCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(decl(anyOf(
    cxxMethodDecl(
      isOverride(),
      isUserProvided(),
      unless(isFinal()),
      hasParent(cxxRecordDecl(isFinal()))).bind("nonfinal"),
    cxxMethodDecl(
      isVirtualAsWritten(),
      isUserProvided(),
      unless(isOverride()),
      hasParent(cxxRecordDecl(isFinal()))).bind("virtual")
    )),
    this);
}

void ClassFinalFunctionCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *NonFinal = Result.Nodes.getNodeAs<CXXMethodDecl>("nonfinal");
  if (NonFinal) {
    const auto Loc = NonFinal->getLocation();
    if (Loc.isInvalid())
      return;

    const auto Mgr = Result.SourceManager;
    if (Mgr->getFileID(Loc) != Mgr->getMainFileID())
      return;

    diag(Loc, "overridden function not marked 'final' in final class");
    return;
  }

  const auto *Virtual = Result.Nodes.getNodeAs<CXXMethodDecl>("virtual");
  if (Virtual) {
    const auto Loc = Virtual->getLocation();
    if (Loc.isInvalid())
      return;

    const auto Mgr = Result.SourceManager;
    if (Mgr->getFileID(Loc) != Mgr->getMainFileID())
      return;

    diag(Loc, "non-overridden virtual function in final class");
    return;
  }
}

} // namespace bsl
} // namespace tidy
} // namespace clang
