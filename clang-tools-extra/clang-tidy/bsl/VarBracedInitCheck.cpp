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

AST_MATCHER(VarDecl, isCXXForRangeDecl) {
  return Node.isCXXForRangeDecl();
}

void VarBracedInitCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
    varDecl(hasInitializer(expr()),
            unless(anyOf(isImplicit(),
                         parmVarDecl(),
                         isCXXForRangeDecl(),
                         hasListInitStyle()))).bind("var"),
    this);
}

void VarBracedInitCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Var = Result.Nodes.getNodeAs<VarDecl>("var");
  const auto Loc = Var->getLocation();

  if (Loc.isInvalid())
    return;

  diag(Loc, "variable '%0' is not initialized via direct list initialization")
      << Var->getName();

  return;
}

} // namespace bsl
} // namespace tidy
} // namespace clang
