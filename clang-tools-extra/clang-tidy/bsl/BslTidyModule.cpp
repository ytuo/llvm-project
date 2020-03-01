//===--- BslTidyModule.cpp - clang-tidy----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "FixedWidthInts.h"
#include "LiteralsAsciiOnlyCheck.h"
#include "LiteralsNoOctalCheck.h"
#include "LiteralsUnsignedSuffixCheck.h"
#include "LiteralsUppercaseSuffixCheck.h"

namespace clang {
namespace tidy {
namespace bsl {

class BslModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<FixedWidthInts>(
        "bsl-fixed-width-ints");
    CheckFactories.registerCheck<LiteralsAsciiOnlyCheck>(
        "bsl-literals-ascii-only");
    CheckFactories.registerCheck<LiteralsNoOctalCheck>(
        "bsl-literals-no-octal");
    CheckFactories.registerCheck<LiteralsUnsignedSuffixCheck>(
        "bsl-literals-unsigned-suffix");
    CheckFactories.registerCheck<LiteralsUppercaseSuffixCheck>(
        "bsl-literals-uppercase-suffix");
  }
};

static ClangTidyModuleRegistry::Add<BslModule>
    X("bsl-module", "Add checks used by the bareflank support library.");

} // namespace bsl

// This anchor is used to force the linker to link in the generated object file
// and thus register the BslModule.
volatile int BslModuleAnchorSource = 0;

} // namespace tidy
} // namespace clang
