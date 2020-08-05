//===--- LiteralsUserDefinedCheck.cpp - clang-tidy ------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "LiteralsUserDefinedCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void LiteralsUserDefinedCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(userDefinedLiteral().bind("literal"), this);
}

void LiteralsUserDefinedCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *UDL = Result.Nodes.getNodeAs<UserDefinedLiteral>("literal");

  const auto Loc = UDL->getBeginLoc();
  if (Loc.isInvalid())
    return;

  diag(Loc, "user-defined literals are forbidden");
}

} // namespace bsl
} // namespace tidy
} // namespace clang
