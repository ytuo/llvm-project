//===--- FixedWidthInts.cpp - clang-tidy---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "FixedWidthInts.h"
#include "clang/Basic/IdentifierTable.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {

// This function is taken from ../google/IntegerTypesCheck.cpp. The check
// below is similar except that is matches additional keywords and doesn't
// provide a suggested replacement.
static Token getTokenAtLoc(SourceLocation Loc,
                           const MatchFinder::MatchResult &MatchResult,
                           IdentifierTable &IdentTable) {
  Token Tok;

  if (Lexer::getRawToken(Loc, Tok, *MatchResult.SourceManager,
                         MatchResult.Context->getLangOpts(), false))
    return Tok;

  if (Tok.is(tok::raw_identifier)) {
    IdentifierInfo &Info = IdentTable.get(Tok.getRawIdentifier());
    Tok.setIdentifierInfo(&Info);
    Tok.setKind(Info.getTokenID());
  }

  return Tok;
}

namespace tidy {
namespace bsl {

void FixedWidthInts::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(typeLoc(loc(isInteger())).bind("loc"), this);
  IdentTable = std::make_unique<IdentifierTable>(getLangOpts());
}

void FixedWidthInts::check(const MatchFinder::MatchResult &Result) {
  auto TL = *Result.Nodes.getNodeAs<TypeLoc>("loc");
  auto Loc = TL.getBeginLoc();
  auto Man = Result.SourceManager;

  if (Loc.isInvalid() || Loc.isMacroID())
    return;

  if (Man->getFileID(Loc) != Man->getMainFileID())
    return;

  if (auto QL = TL.getAs<QualifiedTypeLoc>())
    TL = QL.getUnqualifiedLoc();

  auto Builtin = TL.getAs<BuiltinTypeLoc>();
  if (!Builtin)
    return;

  auto Tok = getTokenAtLoc(Loc, Result, *IdentTable);
  if (!Tok.isOneOf(tok::kw_short, tok::kw_long, tok::kw_signed,
                   tok::kw_unsigned, tok::kw_char, tok::kw_int,
                   tok::kw_wchar_t))
    return;

  diag(Loc, "replace %0 with a fixed-width type") << Builtin.getType();
}

} // namespace bsl
} // namespace tidy
} // namespace clang
