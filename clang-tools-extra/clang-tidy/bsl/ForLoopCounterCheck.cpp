//===--- ForLoopCounterCheck.cpp - clang-tidy ------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ForLoopCounterCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void ForLoopCounterCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(expr(floatLiteral(), unless(hasParent(varDecl(hasInitializer(hasType(realFloatingPointType())))))).bind("floatlit"), this);

  Finder->addMatcher(varDecl(hasType(realFloatingPointType())).bind("floatvar"), this);

  Finder->addMatcher(forStmt(hasIncrement(binaryOperator(hasOperatorName(",")))).bind("singlecounter"), this);
}

void ForLoopCounterCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *ForIncSingle = Result.Nodes.getNodeAs<ForStmt>("singlecounter");
  auto Mgr = Result.SourceManager;

  if (ForIncSingle) {
      auto LocS = ForIncSingle->getInc()->getExprLoc();
      if (LocS.isInvalid() || LocS.isMacroID())
        return;

      if (Mgr->getFileID(LocS) != Mgr->getMainFileID())
        return;

      diag(LocS, "for loop must have single loop-counter");
  }

  const auto *FloatEx = Result.Nodes.getNodeAs<Expr>("floatlit");
  if (FloatEx) {
    auto LocF = FloatEx->getExprLoc();
    if (LocF.isInvalid() || LocF.isMacroID())
        return;

    if (Mgr->getFileID(LocF) != Mgr->getMainFileID())
      return;

    diag(LocF, "float type not allowed (literal)");
  }

  const auto *FloatVar = Result.Nodes.getNodeAs<VarDecl>("floatvar");
  if (FloatVar) {
      auto LocFV = FloatVar->getBeginLoc();
      if (LocFV.isInvalid() || LocFV.isMacroID())
          return;

      if (Mgr->getFileID(LocFV) != Mgr->getMainFileID())
        return;

      diag(LocFV, "float type not allowed (variable declaration)");
  }
}

} // namespace bsl
} // namespace tidy
} // namespace clang
