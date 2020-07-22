//===--- PreprocessorUsageCheck.cpp - clang-tidy --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PreprocessorUsageCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {


namespace {

class PreprocessorUsageCallbacks : public PPCallbacks {
  enum DirectiveKind { DK_If = 0, DK_Ifdef = 1, DK_Ifndef = 2 };

public:
  explicit PreprocessorUsageCallbacks(ClangTidyCheck &Check,
                                          Preprocessor &PP)
      : Check(Check), PP(PP) {}

      // 
      // pp.HandleDirective, isParsingIforElif, isMacroDefined(), 
          // is currentLexer? currentfilelexer?
      // evaluatehasinclude, evaluate defined
      // preprocessedEntity/Directive?
      // preprocessor MacroUse (?)
      // PPDirectives Preprocessor::HandleLineDirective, Preprocessor::HandleUserDiagnosticDirective

  void InclusionDirective(SourceLocation HashLoc, const Token &IncludeTok, StringRef FileName, 
      bool IsAngled, CharSourceRange FilenameRange, const FileEntry *File, StringRef SearchPath, 
      StringRef RelativePath, const Module *Imported, SrcMgr::CharacteristicKind FileType) {
    Check.diag(HashLoc, "InclusionDirective");
  }

  void MacroDefined(const Token &MacroNameTok, const MacroDirective *MD) {
    Check.diag(MacroNameTok.getLocation(), "MacroDirective");
  }    // error

  void PragmaDirective(SourceLocation Loc, PragmaIntroducerKind Introducer) {
    Check.diag(Loc, "PragmaDirective");
  }   // error

  void MacroUndefined(const Token &MacroNameTok, const MacroDefinition &MD, const MacroDirective *Undef) {
    Check.diag(MacroNameTok.getLocation(), "MacroUndefined");
  }  // error


  void If(SourceLocation Loc, SourceRange ConditionRange,
          ConditionValueKind ConditionValue) override {
  }

  void Ifdef(SourceLocation Loc, const Token &MacroNameTok,
             const MacroDefinition &MacroDefinition) override {
    Check.diag(Loc, "hello");
  }

  void Ifndef(SourceLocation Loc, const Token &MacroNameTok,
              const MacroDefinition &MacroDefinition) override {
  }

  void Endif(SourceLocation Loc, SourceLocation IfLoc) override {

  }

  ClangTidyCheck &Check;
  Preprocessor &PP;
};
} // namespace



void PreprocessorUsageCheck::registerPPCallbacks(
    const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
  PP->addPPCallbacks(
      ::std::make_unique<PreprocessorUsageCallbacks>(*this, *PP));
}


} // namespace bsl
} // namespace tidy
} // namespace clang
