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
// #include <unordered_map>
// #include <unordered_set>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void UsingIdentUniqueNamespaceCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(typeAliasDecl().bind("x"), this);  // typealiastemplatedecl
}

void UsingIdentUniqueNamespaceCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *D = Result.Nodes.getNodeAs<TypeAliasDecl>("x");
  std::string name = D->getNameAsString();
  // auto ns = D->getDeclContext();
  // diag(D->getLocation(), "%0 %1") << ns->getEnclosingNamespaceContext() << name;

  // nested namespaces?
  const DeclContext *ns = D->getDeclContext()->getEnclosingNamespaceContext();

  auto itr = namespaceToIDs.find(ns);
  if (itr != namespaceToIDs.end()) {
    auto id_itr = (itr->second).find(name);
    if (id_itr != (itr->second).end()) {
      diag(D->getLocation(), "%0 %1") << ns << name;
        // diag(D->getLocation(), "%0 %1") << ns.getEnclosingNamespaceContext() << name;
    } else {
      (itr->second).insert(name);
    }
    
  } else {
    namespaceToIDs[ns] = {name};
  }

}

} // namespace bsl
} // namespace tidy
} // namespace clang
