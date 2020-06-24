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
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

struct map_entry {
  std::string og_name;
  SourceLocation loc;
};

std::unordered_map<std::string, map_entry> idNames;

void IdentifierTypographicallyUnambiguousCheck::registerMatchers(
    MatchFinder *Finder) {
  Finder->addMatcher(namedDecl().bind("id"), this);
}

void IdentifierTypographicallyUnambiguousCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<NamedDecl>("id");
  auto Mgr = Result.SourceManager;

  if (MatchedDecl) {
    auto Loc = MatchedDecl->getLocation();
    if (Mgr->getFileID(Loc) != Mgr->getMainFileID())
      return;

    std::string og_name = MatchedDecl->getNameAsString();
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
        } else if (name[i] == 'r' && i < name.length() - 1 &&
                   name[i + 1] == 'n') {
          name.replace(i, 2, "m");
        }
        i += 1;
      }
    }

    std::unordered_map<std::string, map_entry>::iterator itr =
        idNames.find(name);
    if (itr != idNames.end()) {
      map_entry m = itr->second;
      std::string og_name = m.og_name;
      unsigned int locnum = Mgr->getPresumedLoc(m.loc).getLine();
      diag(Loc, "Identifier typographically ambiguous with identifier '%0' on "
                "line %1")
          << og_name << locnum;
    } else {
      idNames[name] = map_entry{og_name, Loc};
    }
  }
}

} // namespace bsl
} // namespace tidy
} // namespace clang
