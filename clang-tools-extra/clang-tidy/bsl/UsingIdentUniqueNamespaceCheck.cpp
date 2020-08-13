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
  auto *curns = ns;

  bool seen = false;
  while (curns && (!curns->isTranslationUnit() || curns->isTranslationUnit())) {
    auto itr = namespaceToIDs.find(curns);
    if (itr != namespaceToIDs.end()) {
      auto id_itr = (itr->second).find(name);
      if (id_itr != (itr->second).end()) {
        unsigned int locnum = Mgr->getPresumedLoc(id_itr->second).getLine();
        diag(Loc, "%0 already used in %1 at line %2")
            << name << curns->getEnclosingNamespaceContext() << locnum;
        seen = true;
        break;
      } else if (curns == ns) {
        (itr->second)[name] = Loc;
      }

    } else if (curns == ns) {
      namespaceToIDs[curns] = {{name, Loc}};
    }
    curns = curns->getParent(); // if isTranslationUnit, curns parent is null
  }

}

} // namespace bsl
} // namespace tidy
} // namespace clang
