//===--- ForwardReferenceOverloadedCheck.h - clang-tidy ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_BSL_FORWARDREFERENCEOVERLOADEDCHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_BSL_FORWARDREFERENCEOVERLOADEDCHECK_H

#include "../ClangTidyCheck.h"
#include <unordered_map>
#include <vector>

namespace clang {
namespace tidy {
namespace bsl {

/// Checks that a function that containing a “forwarding reference” as its
/// argument is not overloaded unless the overload has a different number of
/// parameters
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/bsl-forward-reference-overloaded.html
class ForwardReferenceOverloadedCheck : public ClangTidyCheck {
public:
  ForwardReferenceOverloadedCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
  bool isLanguageVersionSupported(const LangOptions &LangOpts) const override {
    return LangOpts.CPlusPlus11;
  }

private:
  std::unordered_map<std::string, std::vector<const FunctionDecl *>>
      overloadedFunctions;
  std::unordered_map<std::string, std::vector<const FunctionDecl *>>
      nonForwardRefFunctions;
};

} // namespace bsl
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_BSL_FORWARDREFERENCEOVERLOADEDCHECK_H
