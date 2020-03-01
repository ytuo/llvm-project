//===--- TypesFixedWidthIntsCheck.cpp - clang-tidy---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "TypesFixedWidthIntsCheck.h"
#include "BslCheckUtils.h"
#include "clang/Basic/IdentifierTable.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void TypesFixedWidthIntsCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(typeLoc(loc(isInteger())).bind("loc"), this);
  IdentTable = std::make_unique<IdentifierTable>(getLangOpts());
}

void TypesFixedWidthIntsCheck::check(const MatchFinder::MatchResult &Result) {
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
