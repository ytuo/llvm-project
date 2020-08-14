//===--- UnusedReturnValueCheck.cpp - clang-tidy --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "UnusedReturnValueCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void UnusedReturnValueCheck::registerMatchers(MatchFinder *Finder) {
  // static_cast<void>(foo()), where foo() returns non-void, and overloaded
  // built-in operators are exceptions to this check:
  auto StaticVoidCast = cxxStaticCastExpr(hasDestinationType(voidType()));
  auto AllowedExprs = anyOf(cxxOperatorCallExpr(),
                            hasParent(StaticVoidCast),
                            hasParent(constantExpr(hasParent(caseStmt())))
                      );

  auto NonVoidFunc = functionDecl(unless(
    anyOf(returns(voidType()),
          hasAttr(clang::attr::Unused),
          cxxMethodDecl(isMoveAssignmentOperator()),
          cxxMethodDecl(isCopyAssignmentOperator()))));

  auto CheckedCall = callExpr(unless(AllowedExprs), callee(NonVoidFunc));
  auto IgnoredCall = ignoringImplicit(ignoringParenImpCasts(CheckedCall));
  auto IgnoredExpr = expr(IgnoredCall).bind("unused-ret");

  auto UnusedInDoStmt = doStmt(hasBody(IgnoredExpr));
  auto UnusedInCaseStmt = switchCase(forEach(IgnoredExpr));
  auto UnusedInWhileStmt = whileStmt(hasBody(IgnoredExpr));
  auto UnusedInCompoundStmt = compoundStmt(forEach(IgnoredExpr));
  auto UnusedInRangeForStmt = cxxForRangeStmt(hasBody(IgnoredExpr));
  auto UnusedInIfStmt = ifStmt(eachOf(hasThen(IgnoredExpr),
                                      hasElse(IgnoredExpr)));
  auto UnusedInForStmt = forStmt(eachOf(hasLoopInit(IgnoredExpr),
                                        hasIncrement(IgnoredExpr),
                                        hasBody(IgnoredExpr)));

  Finder->addMatcher(
    stmt(anyOf(UnusedInDoStmt, UnusedInCaseStmt, UnusedInWhileStmt,
               UnusedInCompoundStmt, UnusedInRangeForStmt, UnusedInIfStmt,
               UnusedInForStmt)),
    this);
}

void UnusedReturnValueCheck::check(const MatchFinder::MatchResult &Result) {
  auto Call = Result.Nodes.getNodeAs<CallExpr>("unused-ret");
  if (!Call)
    return;

  diag(Call->getBeginLoc(), "unused return value");
}

} // namespace bsl
} // namespace tidy
} // namespace clang
