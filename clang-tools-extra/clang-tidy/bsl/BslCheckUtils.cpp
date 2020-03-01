//===--- BslCheckUtils.cpp - clang-tidy -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "BslCheckUtils.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

StringRef getRawTokenStr(SourceLocation Loc,
                         const MatchFinder::MatchResult &Result) {
  if (Loc.isInvalid() || Loc.isMacroID())
    return StringRef();

  auto Mgr = Result.SourceManager;
  if (Mgr->getFileID(Loc) != Mgr->getMainFileID())
    return StringRef();

  auto Ctx = Result.Context;

  Token Tok;
  if (Lexer::getRawToken(Loc, Tok, *Mgr, Ctx->getLangOpts(), false))
    return StringRef();

  auto Buf = Tok.getLiteralData();
  if (!Buf)
    return StringRef();

  return StringRef(Buf, Tok.getLength());
}

} // namespace bsl
} // namespace tidy
} // namespace clang
