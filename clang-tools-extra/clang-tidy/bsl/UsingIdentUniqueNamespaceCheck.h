//===--- UsingIdentUniqueNamespaceCheck.h - clang-tidy ----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_BSL_USINGIDENTUNIQUENAMESPACECHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_BSL_USINGIDENTUNIQUENAMESPACECHECK_H

#include "../ClangTidyCheck.h"
#include <unordered_map>
#include <unordered_set>

namespace clang {
namespace tidy {
namespace bsl {

/// Check that a "using" name is a unique identifier in a namespace
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/bsl-using-ident-unique-namespace.html
class UsingIdentUniqueNamespaceCheck : public ClangTidyCheck {
public:
  UsingIdentUniqueNamespaceCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;

private:
	std::unordered_map<const DeclContext *, std::unordered_set<std::string>> namespaceToIDs;
};

} // namespace bsl
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_BSL_USINGIDENTUNIQUENAMESPACECHECK_H
