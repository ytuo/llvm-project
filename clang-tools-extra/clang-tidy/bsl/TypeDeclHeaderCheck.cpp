//===--- TypeDeclHeaderCheck.cpp - clang-tidy -----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "TypeDeclHeaderCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void TypeDeclHeaderCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(tagDecl(unless(hasAncestor(tagDecl()))).bind("tag"), this);
}

void TypeDeclHeaderCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<TagDecl>("tag");
  SourceManager &SM = *Result.SourceManager;

  StringRef TypeName = MatchedDecl->getName();

  StringRef FileNameWithPath =
      SM.getFilename(SM.getSpellingLoc(MatchedDecl->getLocation()));

  const FileEntry *fe =
      SM.getFileEntryForID(SM.getFileID(MatchedDecl->getLocation()));
  StringRef filedir = fe->getDir()->getName();
  if (FileNameWithPath.consume_back(StringRef(".h")) ||
      FileNameWithPath.consume_back(StringRef(".hpp"))) {
    // remove path
    FileNameWithPath.consume_front(filedir);
    FileNameWithPath.consume_front(StringRef("/"));
    if (FileNameWithPath.compare(TypeName)) {
      diag(MatchedDecl->getLocation(),
           "declared type name %0 does not have same name as header file %1")
          << TypeName << FileNameWithPath;
    }
  }
}

} // namespace bsl
} // namespace tidy
} // namespace clang
