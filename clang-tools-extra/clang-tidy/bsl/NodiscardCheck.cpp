//===--- NodiscardCheck.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NodiscardCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void NodiscardCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
    functionDecl(
      unless(
        anyOf(
          returns(voidType()),
          isNoReturn(),
          isImplicit(),
          hasAttr(clang::attr::Unused),
          hasAttr(clang::attr::WarnUnusedResult)
        )
      )
    ).bind("decl"),
    this
  );
}

void NodiscardCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Decl = Result.Nodes.getNodeAs<FunctionDecl>("decl");
  const auto Loc = Decl->getLocation();

  if (Loc.isInvalid())
    return;

  if (Decl->getFriendObjectKind() != clang::Decl::FriendObjectKind::FOK_None) {
    return;
  }

  if (dyn_cast<CXXDeductionGuideDecl>(Decl))
    return;

  diag(Loc, "function %0 should be marked [[nodiscard]] or [[maybe_unused]]") << Decl;
}

} // namespace bsl
} // namespace tidy
} // namespace clang
