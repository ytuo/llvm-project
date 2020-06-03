//===------- BslTestTidyTestModule.cpp - clang-tidy -----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "ForLoopCheck.h"
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsltest {

class BslTestModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<ForLoopCheck>(
        "bsltest-for-loop");
  }
};

// Register the BslTestModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<BslTestModule> X("bsl-test-module",
                                                   "Add additional bsl checks.");

} // namespace bsltest

// This anchor is used to force the linker to link in the generated object file
// and thus register the BslTestModule.
volatile int BslTestModuleAnchorSource = 0;

} // namespace tidy
} // namespace clang
