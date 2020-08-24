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
#include "AssignOpDeclRefQualifierCheck.h"
#include "AutoTypeUsageCheck.h"
#include "BooleanOperatorsForbiddenCheck.h"
#include "ClassBaseCheck.h"
#include "ClassFinalFunctionCheck.h"
#include "ClassMemberInitCheck.h"
#include "ClassMemberRedefinedCheck.h"
#include "ClassVirtualBaseCheck.h"
#include "ComparisonOperatorsForbiddenCheck.h"
#include "CopyMoveAccessSpecifierCheck.h"
#include "ConstObjStdMoveCheck.h"
#include "DeclForbiddenCheck.h"
#include "DestructorAccessSpecifierCheck.h"
#include "ElseRequiredAfterIfCheck.h"
#include "EnumExplicitCheck.h"
#include "EnumInitCheck.h"
#include "EnumScopedCheck.h"
#include "ForLoopCounterCheck.h"
#include "ForwardReferenceOverloadedCheck.h"
#include "FunctionNameUseCheck.h"
#include "FunctionNoexceptCheck.h"
#include "IdentifierTypographicallyUnambiguousCheck.h"
#include "LambdaImplicitCaptureCheck.h"
#include "LambdaParamListCheck.h"
#include "LiteralsAsciiOnlyCheck.h"
#include "LiteralsDigitSeparatorCheck.h"
#include "LiteralsNoOctalCheck.h"
#include "LiteralsUnsignedSuffixCheck.h"
#include "LiteralsUserDefinedCheck.h"
#include "NamespaceGlobalCheck.h"
#include "NonPodClassdefCheck.h"
#include "NonPodStaticCheck.h"
#include "OpBitwiseOperandsCheck.h"
#include "OpConditionalSubexprCheck.h"
#include "OpEqualityVirtMemfnNullptrCheck.h"
#include "OpForbiddenOverloadCheck.h"
#include "OpLogicalPostfixCheck.h"
#include "OpMixedIncrementDecrementCheck.h"
#include "OpRelationalReturnBoolCheck.h"
#include "PureOverrideCheck.h"
#include "SpecialMemberFunctionsCheck.h"
#include "StmtForbiddenCheck.h"
#include "StmtSwitchCaseParentCheck.h"
#include "StmtSwitchDefaultBreakCheck.h"
#include "StmtSwitchDefaultLastCheck.h"
#include "StructDefCheck.h"
#include "TemplateGenericParamCheck.h"
#include "TernaryOperatorForbiddenCheck.h"
#include "TypesFixedWidthIntsCheck.h"
#include "TypesNoWideCharCheck.h"
#include "UnusedReturnValueCheck.h"
#include "UsingDeclScopeCheck.h"
#include "UsingIdentUniqueNamespaceCheck.h"
#include "VarBracedInitCheck.h"

namespace clang {
namespace tidy {
namespace bsl {

class BslModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<AssignOpDeclRefQualifierCheck>(
        "bsl-assign-op-decl-ref-qualifier");
    CheckFactories.registerCheck<AutoTypeUsageCheck>(
        "bsl-auto-type-usage");
    CheckFactories.registerCheck<BooleanOperatorsForbiddenCheck>(
        "bsl-boolean-operators-forbidden");
    CheckFactories.registerCheck<ClassBaseCheck>(
        "bsl-class-base");
    CheckFactories.registerCheck<ClassFinalFunctionCheck>(
        "bsl-class-final-function");
    CheckFactories.registerCheck<ClassMemberInitCheck>(
        "bsl-class-member-init");
    CheckFactories.registerCheck<ClassMemberRedefinedCheck>(
        "bsl-class-member-redefined");
    CheckFactories.registerCheck<ClassVirtualBaseCheck>(
        "bsl-class-virtual-base");
    CheckFactories.registerCheck<ComparisonOperatorsForbiddenCheck>(
        "bsl-comparison-operators-forbidden");
    CheckFactories.registerCheck<CopyMoveAccessSpecifierCheck>(
        "bsl-copy-move-access-specifier");
    CheckFactories.registerCheck<ConstObjStdMoveCheck>(
        "bsl-const-obj-std-move");
    CheckFactories.registerCheck<DeclForbiddenCheck>(
        "bsl-decl-forbidden");
    CheckFactories.registerCheck<DestructorAccessSpecifierCheck>(
        "bsl-destructor-access-specifier");
    CheckFactories.registerCheck<ElseRequiredAfterIfCheck>(
        "bsl-else-required-after-if");
    CheckFactories.registerCheck<EnumExplicitCheck>(
        "bsl-enum-explicit");
    CheckFactories.registerCheck<EnumInitCheck>(
        "bsl-enum-init");
    CheckFactories.registerCheck<EnumScopedCheck>(
        "bsl-enum-scoped");
    CheckFactories.registerCheck<ForLoopCounterCheck>(
        "bsl-for-loop-counter");
    CheckFactories.registerCheck<ForwardReferenceOverloadedCheck>(
        "bsl-forward-reference-overloaded");
    CheckFactories.registerCheck<FunctionNameUseCheck>(
        "bsl-function-name-use");
    CheckFactories.registerCheck<FunctionNoexceptCheck>(
        "bsl-function-noexcept");
    CheckFactories.registerCheck<IdentifierTypographicallyUnambiguousCheck>(
        "bsl-identifier-typographically-unambiguous");    
    CheckFactories.registerCheck<LambdaImplicitCaptureCheck>(
        "bsl-lambda-implicit-capture");
    CheckFactories.registerCheck<LambdaParamListCheck>(
        "bsl-lambda-param-list");
    CheckFactories.registerCheck<LiteralsDigitSeparatorCheck>(
        "bsl-literals-digit-separator");
    CheckFactories.registerCheck<LiteralsUserDefinedCheck>(
        "bsl-literals-user-defined");
    CheckFactories.registerCheck<NamespaceGlobalCheck>(
        "bsl-namespace-global");
    CheckFactories.registerCheck<NonPodClassdefCheck>(
        "bsl-non-pod-classdef");
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
    CheckFactories.registerCheck<OpLogicalPostfixCheck>(
        "bsl-op-logical-postfix");
    CheckFactories.registerCheck<OpMixedIncrementDecrementCheck>(
        "bsl-op-mixed-increment-decrement");
    CheckFactories.registerCheck<OpRelationalReturnBoolCheck>(
        "bsl-op-relational-return-bool");
    CheckFactories.registerCheck<PureOverrideCheck>(
        "bsl-pure-override");
    CheckFactories.registerCheck<SpecialMemberFunctionsCheck>(
        "bsl-special-member-functions");
    CheckFactories.registerCheck<StmtForbiddenCheck>(
        "bsl-stmt-forbidden");
    CheckFactories.registerCheck<StmtSwitchCaseParentCheck>(
        "bsl-stmt-switch-case-parent");
    CheckFactories.registerCheck<StmtSwitchDefaultBreakCheck>(
        "bsl-stmt-switch-default-break");
    CheckFactories.registerCheck<StmtSwitchDefaultLastCheck>(
        "bsl-stmt-switch-default-last");
    CheckFactories.registerCheck<StructDefCheck>(
        "bsl-struct-def");
    CheckFactories.registerCheck<TemplateGenericParamCheck>(
        "bsl-template-generic-param");
    CheckFactories.registerCheck<TernaryOperatorForbiddenCheck>(
        "bsl-ternary-operator-forbidden");
    CheckFactories.registerCheck<TypesFixedWidthIntsCheck>(
        "bsl-types-fixed-width-ints");
    CheckFactories.registerCheck<LiteralsAsciiOnlyCheck>(
        "bsl-literals-ascii-only");
    CheckFactories.registerCheck<LiteralsNoOctalCheck>(
        "bsl-literals-no-octal");
    CheckFactories.registerCheck<LiteralsUnsignedSuffixCheck>(
        "bsl-literals-unsigned-suffix");
    CheckFactories.registerCheck<TypesNoWideCharCheck>(
        "bsl-types-no-wide-char");
    CheckFactories.registerCheck<UnusedReturnValueCheck>(
        "bsl-unused-return-value");
    CheckFactories.registerCheck<UsingDeclScopeCheck>(
        "bsl-using-decl-scope");
    CheckFactories.registerCheck<UsingIdentUniqueNamespaceCheck>(
        "bsl-using-ident-unique-namespace");
    CheckFactories.registerCheck<VarBracedInitCheck>(
        "bsl-var-braced-init");
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
