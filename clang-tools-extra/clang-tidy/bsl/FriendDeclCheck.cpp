//===--- FriendDeclCheck.cpp - clang-tidy ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "FriendDeclCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void FriendDeclCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(friendDecl().bind("friend"), this);
}

void FriendDeclCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Friend = Result.Nodes.getNodeAs<FriendDecl>("friend");

  const auto Loc = Friend->getBeginLoc();
  if (Loc.isInvalid())
    return;

  diag(Loc, "friend declarations are forbidden");
}

} // namespace bsl
} // namespace tidy
} // namespace clang
