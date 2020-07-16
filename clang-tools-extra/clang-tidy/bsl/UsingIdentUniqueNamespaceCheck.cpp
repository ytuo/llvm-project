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
  Finder->addMatcher(typeAliasDecl().bind("x"), this);
}

void UsingIdentUniqueNamespaceCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *D = Result.Nodes.getNodeAs<TypeAliasDecl>("x");
  const auto Loc = D->getBeginLoc();
  if (Loc.isInvalid())
    return;

  auto Mgr = Result.SourceManager;
  if (Mgr->getFileID(Loc) != Mgr->getMainFileID())
    return;

  std::string name = D->getNameAsString();
  const DeclContext *ns = D->getDeclContext()->getEnclosingNamespaceContext();

  while (!ns->isTranslationUnit()) {
    auto itr = namespaceToIDs.find(ns);
    if (itr != namespaceToIDs.end()) {
      auto id_itr = (itr->second).find(name);
      if (id_itr != (itr->second).end()) {
        unsigned int locnum = Mgr->getPresumedLoc(id_itr->second).getLine();
        diag(Loc, "%0 already used in current namespace %1 at line %2")
            << name << ns->getEnclosingNamespaceContext() << locnum;
        break;
      } else {
        (itr->second)[name] = Loc;
      }

    } else {
      namespaceToIDs[ns] = {{name, Loc}};
    }
    ns = ns->getParent();
  }
}

} // namespace bsl
} // namespace tidy
} // namespace clang
