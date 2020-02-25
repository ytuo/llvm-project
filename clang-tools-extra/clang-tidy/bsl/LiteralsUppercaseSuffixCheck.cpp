//===--- LiteralsUppercaseSuffixCheck.cpp - clang-tidy --------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "LiteralsUppercaseSuffixCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void LiteralsUppercaseSuffixCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(integerLiteral().bind("lit"), this);
}

void LiteralsUppercaseSuffixCheck::check(const MatchFinder::MatchResult &Result) {
  auto Lit = Result.Nodes.getNodeAs<IntegerLiteral>("lit");
  auto Loc = Lit->getBeginLoc();
  auto Mgr = Result.SourceManager;
  auto Ctx = Result.Context;

  if (Loc.isInvalid() || Loc.isMacroID())
    return;

  if (Mgr->getFileID(Loc) != Mgr->getMainFileID())
    return;

  Token Tok;
  if (Lexer::getRawToken(Loc, Tok, *Mgr, Ctx->getLangOpts(), false))
    return;

  auto Buf = Tok.getLiteralData();
  if (!Buf)
    return;

  StringRef Str(Buf, Tok.getLength());

  if (Str.find_first_of("ul") != StringRef::npos) {
    diag(Loc, "integer literal suffix is not uppercase");
    return;
  }
}

} // namespace bsl
} // namespace tidy
} // namespace clang
