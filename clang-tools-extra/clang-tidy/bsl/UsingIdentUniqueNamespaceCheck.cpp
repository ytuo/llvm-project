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
  Finder->addMatcher(typeAliasDecl().bind("using"), this);
  Finder->addMatcher(
      tagDecl(anyOf(cxxRecordDecl(hasDefinition()), enumDecl())).bind("tag"),
      this);
  Finder->addMatcher(typedefDecl().bind("typedef"), this);
}

void UsingIdentUniqueNamespaceCheck::check(
    const MatchFinder::MatchResult &Result) {
  auto Mgr = Result.SourceManager;

  const auto *D = Result.Nodes.getNodeAs<TypeAliasDecl>("using");
  if (D) {

    const auto Loc = D->getBeginLoc();
    if (Loc.isInvalid())
      return;

    std::string name = D->getNameAsString();
    const DeclContext *ns = D->getDeclContext();
    auto *curns = ns;

    findPreviousUsage(curns, name, ns, Mgr, Loc);
  }

  const auto *MatchedDecl = Result.Nodes.getNodeAs<TagDecl>("tag");
  if (MatchedDecl) {
    const auto Loc = MatchedDecl->getBeginLoc();
    if (Loc.isInvalid())
      return;

    std::string name = MatchedDecl->getNameAsString();
    const DeclContext *ns = MatchedDecl->getDeclContext();
    auto *curns = ns;

    findPreviousUsage(curns, name, ns, Mgr, Loc);
  }

  const auto *TypedefMatchDecl = Result.Nodes.getNodeAs<TypedefDecl>("typedef");
  if (TypedefMatchDecl) {
    const auto Loc = TypedefMatchDecl->getBeginLoc();
    if (Loc.isInvalid())
      return;

    std::string name = TypedefMatchDecl->getNameAsString();
    const DeclContext *ns = TypedefMatchDecl->getDeclContext();
    auto *curns = ns;

    findPreviousUsage(curns, name, ns, Mgr, Loc);
  }
}

void UsingIdentUniqueNamespaceCheck::findPreviousUsage(const DeclContext *curns,
                                                       std::string name,
                                                       const DeclContext *ns,
                                                       SourceManager *Mgr,
                                                       SourceLocation Loc) {
  // bool seen = false;
  while (curns) {
    auto itr = namespaceToIDs.find(curns);
    if (itr != namespaceToIDs.end()) {
      auto id_itr = (itr->second).find(name);
      if (id_itr != (itr->second).end()) {
        unsigned int locnum = Mgr->getPresumedLoc(id_itr->second).getLine();
        diag(Loc, "%0 already used in %1 at line %2")
            << name << curns->getEnclosingNamespaceContext() << locnum;
        // seen = true;
        break;
      } else if (curns ==
                 ns) { // Could add at end of while loop if no match instead
        (itr->second)[name] = Loc;
      }

    } else if (curns == ns) {
      namespaceToIDs[curns] = {{name, Loc}};
    }
    curns = curns->getLexicalParent();
  }
}

} // namespace bsl
} // namespace tidy
} // namespace clang
