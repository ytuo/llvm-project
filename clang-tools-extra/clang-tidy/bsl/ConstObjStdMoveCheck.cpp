//===--- ConstObjStdMoveCheck.cpp - clang-tidy ----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ConstObjStdMoveCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void ConstObjStdMoveCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      callExpr(
          hasArgument(0, declRefExpr(hasType(qualType(isConstQualified())))))
          .bind("const"),
      this);
}

void ConstObjStdMoveCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<CallExpr>("const");
  if (MatchedDecl->isCallToStdMove()) {
    diag(MatchedDecl->getBeginLoc(),
         "std::move should not be used on objects declared const or const &");
  } else {
    const FunctionDecl *FD = MatchedDecl->getDirectCallee();
    const auto *NsDecl = cast<NamespaceDecl>(
        FD->getDeclContext()->getEnclosingNamespaceContext());

    if (FD->getIdentifier()->isStr("move") &&
        NsDecl->getName().equals(StringRef("bsl"))) {
      diag(MatchedDecl->getBeginLoc(),
           "bsl::move should not be used on objects declared const or const &");
    }
  }
}

} // namespace bsl
} // namespace tidy
} // namespace clang
