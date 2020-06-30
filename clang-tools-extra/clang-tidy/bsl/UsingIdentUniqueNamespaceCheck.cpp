//===--- UsingIdentUniqueNamespaceCheck.cpp - clang-tidy ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "UsingIdentUniqueNamespaceCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void UsingIdentUniqueNamespaceCheck::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(typeAliasDecl().bind("x"), this);  // typealiastemplatedecl
}

void UsingIdentUniqueNamespaceCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *D = Result.Nodes.getNodeAs<TypeAliasDecl>("x");
  // const auto *Prev = D->getPreviousDecl();
  auto It = D->redecls_begin();
  auto EndIt = D->redecls_end();

  if (It == EndIt) {
    diag(D->getLocation(), "z");
    return; 
  }

  if (D->isFirstDecl()) {
  diag(D->getLocation(), "zzz");

  }

  // // const auto t = D->getDescribedAliasTemplate();
  // if (D->isCanonicalDecl()) {
  //   diag(D->getLocation(), "none");    
  // }
  // if (t2) {
  //   diag(D->getLocation(), "previously declared here");    
  // }
  // else {
  //   diag(D->getLocation(), "derp"); 
  // }
    
  // if (!Prev->getLocation().isValid())
  //   return;
  // if (Prev->getLocation() == D->getLocation())
  //   return;
  // if (IgnoreMacros &&
  //     (D->getLocation().isMacroID() || Prev->getLocation().isMacroID()))
  //   return;
  // // Don't complain when the previous declaration is a friend declaration.
  // for (const auto &Parent : Result.Context->getParents(*Prev))
  //   if (Parent.get<FriendDecl>())
  //     return;

  // const SourceManager &SM = *Result.SourceManager;

  // const bool DifferentHeaders =
  //     !SM.isInMainFile(D->getLocation()) &&
  //     !SM.isWrittenInSameFile(Prev->getLocation(), D->getLocation());

  // bool MultiVar = false;
  // if (const auto *VD = dyn_cast<VarDecl>(D)) {
  //   // Is this a multivariable declaration?
  //   for (const auto Other : VD->getDeclContext()->decls()) {
  //     if (Other != D && Other->getBeginLoc() == VD->getBeginLoc()) {
  //       MultiVar = true;
  //       break;
  //     }
  //   }
  // }

  // SourceLocation EndLoc = Lexer::getLocForEndOfToken(
  //     D->getSourceRange().getEnd(), 0, SM, Result.Context->getLangOpts());
  // {
  //   auto Diag = diag(D->getLocation(), "redundant %0 declaration") << D;
  //   if (!MultiVar && !DifferentHeaders)
  //     Diag << FixItHint::CreateRemoval(
  //         SourceRange(D->getSourceRange().getBegin(), EndLoc));
  // }
  // diag(Prev->getLocation(), "previously declared here", DiagnosticIDs::Note);
}

} // namespace bsl
} // namespace tidy
} // namespace clang
