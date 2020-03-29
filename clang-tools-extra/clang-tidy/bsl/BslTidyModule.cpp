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
#include "EnumExplicitCheck.h"
#include "EnumInitCheck.h"
#include "EnumScopedCheck.h"
#include "LambdaImplicitCaptureCheck.h"
#include "LambdaParamListCheck.h"
#include "LiteralsAsciiOnlyCheck.h"
#include "LiteralsNoOctalCheck.h"
#include "LiteralsUnsignedSuffixCheck.h"
#include "LiteralsUppercaseSuffixCheck.h"
#include "NonPodStaticCheck.h"
#include "OpBitwiseOperandsCheck.h"
#include "OpConditionalSubexprCheck.h"
#include "OpEqualityVirtMemfnNullptrCheck.h"
#include "OpForbiddenOverloadCheck.h"
#include "OpMixedIncrementDecrementCheck.h"
#include "TypesFixedWidthIntsCheck.h"
#include "TypesNoWideCharCheck.h"
#include "UnusedReturnValueCheck.h"

namespace clang {
namespace tidy {
namespace bsl {

class BslModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<EnumExplicitCheck>(
        "bsl-enum-explicit");
    CheckFactories.registerCheck<EnumInitCheck>(
        "bsl-enum-init");
    CheckFactories.registerCheck<EnumScopedCheck>(
        "bsl-enum-scoped");
    CheckFactories.registerCheck<LambdaImplicitCaptureCheck>(
        "bsl-lambda-implicit-capture");
    CheckFactories.registerCheck<LambdaParamListCheck>(
        "bsl-lambda-param-list");
    CheckFactories.registerCheck<NonPodStaticCheck>(
        "bsl-non-pod-static");
    CheckFactories.registerCheck<OpBitwiseOperandsCheck>(
        "bsl-op-bitwise-operands");
    CheckFactories.registerCheck<OpConditionalSubexprCheck>(
        "bsl-op-conditional-subexpr");
    CheckFactories.registerCheck<OpEqualityVirtMemfnNullptrCheck>(
        "bsl-op-equality-virt-memfn-nullptr");
    CheckFactories.registerCheck<OpForbiddenOverloadCheck>(
        "bsl-op-forbidden-overload");
    CheckFactories.registerCheck<OpMixedIncrementDecrementCheck>(
        "bsl-op-mixed-increment-decrement");
    CheckFactories.registerCheck<TypesFixedWidthIntsCheck>(
        "bsl-types-fixed-width-ints");
    CheckFactories.registerCheck<LiteralsAsciiOnlyCheck>(
        "bsl-literals-ascii-only");
    CheckFactories.registerCheck<LiteralsNoOctalCheck>(
        "bsl-literals-no-octal");
    CheckFactories.registerCheck<LiteralsUnsignedSuffixCheck>(
        "bsl-literals-unsigned-suffix");
    CheckFactories.registerCheck<LiteralsUppercaseSuffixCheck>(
        "bsl-literals-uppercase-suffix");
    CheckFactories.registerCheck<TypesNoWideCharCheck>(
        "bsl-types-no-wide-char");
    CheckFactories.registerCheck<UnusedReturnValueCheck>(
        "bsl-unused-return-value");
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
