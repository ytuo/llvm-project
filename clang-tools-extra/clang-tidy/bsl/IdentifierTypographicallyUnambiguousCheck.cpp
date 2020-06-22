//===--- IdentifierTypographicallyUnambiguousCheck.cpp - clang-tidy -------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "IdentifierTypographicallyUnambiguousCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <unordered_set>
#include <string>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {


std::unordered_set<std::string> idNames;    // make hashmap: map to line #

void IdentifierTypographicallyUnambiguousCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(namedDecl().bind("x"), this);
}

void IdentifierTypographicallyUnambiguousCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<NamedDecl>("x");
  const auto Mgr = Result.SourceManager;
  
  if (MatchedDecl) {
    auto Loc = MatchedDecl->getLocation();
    if (Mgr->getFileID(Loc) != Mgr->getMainFileID())
      return;

    std::string name = MatchedDecl->getName().lower();

    unsigned int i = 0;

    while (i < name.length()) {
      if (name[i] == '_') {
        name.erase(i, 1);
      } else {
        if (name[i] == '0') {
          name.replace(i, 1, "o");
        } else if (name[i] == '1') {
          name.replace(i, 1, "i");
        } else if (name[i] == 'l') {
          name.replace(i, 1, "i");
        } else if (name[i] == '5') {
          name.replace(i, 1, "s");
        } else if (name[i] == '2') {
          name.replace(i, 1, "z");
        } else if (name[i] == 'h') {
          name.replace(i, 1, "n");
        } else if (name[i] == '8') {
          name.replace(i, 1, "b");
        } else if (name[i] == 'r' && i < name.length() - 1 && name[i+1] == 'n') {
          name.replace(i, 2, "m");
        }
        i += 1;
      }
    }

    if (idNames.find(name) != idNames.end()) {
      diag(MatchedDecl->getLocation(), "different identifiers shall be typographically unambiguous");
    } else {
      idNames.insert(name);
    }
  }
}

} // namespace bsl
} // namespace tidy
} // namespace clang
