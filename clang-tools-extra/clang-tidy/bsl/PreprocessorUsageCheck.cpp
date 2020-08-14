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

  PreprocessorUsageCheck::PreprocessorUsageCheck(StringRef Name,
                                           ClangTidyContext *Context)
    : HeaderGuardCheck(Name, Context) {}

std::string PreprocessorUsageCheck::getHeaderGuard(StringRef Filename,
                                                 StringRef OldGuard) {
  std::string Guard = tooling::getAbsolutePath(Filename);

  // Sanitize the path. There are some rules for compatibility with the historic
  // style in include/llvm and include/clang which we want to preserve.

  // We don't want _INCLUDE_ in our guards.
  size_t PosInclude = Guard.rfind("include/");
  if (PosInclude != StringRef::npos)
    Guard = Guard.substr(PosInclude + std::strlen("include/"));

  // For clang we drop the _TOOLS_.
  size_t PosToolsClang = Guard.rfind("tools/clang/");
  if (PosToolsClang != StringRef::npos)
    Guard = Guard.substr(PosToolsClang + std::strlen("tools/"));

  // Unlike LLVM svn, LLVM git monorepo is named llvm-project, so we replace
  // "/llvm-project/" with the cannonical "/llvm/".
  const static StringRef LLVMProject = "/llvm-project/";
  size_t PosLLVMProject = Guard.rfind(std::string(LLVMProject));
  if (PosLLVMProject != StringRef::npos)
    Guard = Guard.replace(PosLLVMProject, LLVMProject.size(), "/llvm/");

  // The remainder is LLVM_FULL_PATH_TO_HEADER_H
  size_t PosLLVM = Guard.rfind("llvm/");
  if (PosLLVM != StringRef::npos)
    Guard = Guard.substr(PosLLVM);

  std::replace(Guard.begin(), Guard.end(), '/', '_');
  std::replace(Guard.begin(), Guard.end(), '.', '_');
  std::replace(Guard.begin(), Guard.end(), '-', '_');

  // The prevalent style in clang is LLVM_CLANG_FOO_BAR_H
  if (StringRef(Guard).startswith("clang"))
    Guard = "LLVM_" + Guard;

  return StringRef(Guard).upper();
}


// namespace {

// class PreprocessorUsageCallbacks : public PPCallbacks {
//   enum DirectiveKind { DK_If = 0, DK_Ifdef = 1, DK_Ifndef = 2 };

// public:
//   explicit PreprocessorUsageCallbacks(ClangTidyCheck *Check,
//                                           Preprocessor *PP)
//       : Check(Check), PP(PP) {}

      // 
      // pp.HandleDirective, isParsingIforElif, isMacroDefined(), 
          // is currentLexer? currentfilelexer?
      // evaluatehasinclude, evaluate defined
      // preprocessedEntity/Directive?
      // preprocessor MacroUse (?)
      // PPDirectives Preprocessor::HandleLineDirective, Preprocessor::HandleUserDiagnosticDirective

// void FileChanged(SourceLocation Loc, FileChangeReason Reason,
//                    SrcMgr::CharacteristicKind FileType,
//                    FileID PrevFID) override {
//     // Record all files we enter. We'll need them to diagnose headers without
//     // guards.
//     SourceManager &SM = PP->getSourceManager();
//     if (Reason == EnterFile && FileType == SrcMgr::C_User) {
//       if (const FileEntry *FE = SM.getFileEntryForID(SM.getFileID(Loc))) {
//         std::string FileName = cleanPath(FE->getName());
//         Files[FileName] = FE;
//       }
//     }
//   }

//   void InclusionDirective(SourceLocation HashLoc, const Token &IncludeTok, StringRef FileName, 
//       bool IsAngled, CharSourceRange FilenameRange, const FileEntry *File, StringRef SearchPath, 
//       StringRef RelativePath, const Module *Imported, SrcMgr::CharacteristicKind FileType) {
//     Check->diag(HashLoc, "InclusionDirective");
//   }

//   // void MacroDefined(const Token &MacroNameTok, const MacroDirective *MD) {
//   //   Check.diag(MacroNameTok.getLocation(), "MacroDirective");
//   // }    // error

//   // void PragmaDirective(SourceLocation Loc, PragmaIntroducerKind Introducer) {
//   //   Check->diag(Loc, "PragmaDirective");
//   // }   // error

//   // void MacroUndefined(const Token &MacroNameTok, const MacroDefinition &MD, const MacroDirective *Undef) {
//   //   Check->diag(MacroNameTok.getLocation(), "MacroUndefined");
//   // }  // error


//   // void If(SourceLocation Loc, SourceRange ConditionRange,
//   //         ConditionValueKind ConditionValue) override {
//   // }

//   // void Ifdef(SourceLocation Loc, const Token &MacroNameTok,
//   //            const MacroDefinition &MacroDefinition) override {
//   //   Check->diag(Loc, "hello");
//   // }

//   // void Ifndef(SourceLocation Loc, const Token &MacroNameTok,
//   //             const MacroDefinition &MacroDefinition) override {
//   // }

//   // void Endif(SourceLocation Loc, SourceLocation IfLoc) override {

//   // }

//   // extra
//   void MacroDefined(const Token &MacroNameTok,
//                     const MacroDirective *MD) override {
//     // Record all defined macros. We store the whole token to get info on the
//     // name later.
//     Macros.emplace_back(MacroNameTok, MD->getMacroInfo());
//   }
//   void EndOfMainFile() override {
//     // Now that we have all this information from the preprocessor, use it!
//     SourceManager &SM = PP->getSourceManager();

//     for (const auto &MacroEntry : Macros) {
//       const MacroInfo *MI = MacroEntry.second;

//       // We use clang's header guard detection. This has the advantage of also
//       // emitting a warning for cases where a pseudo header guard is found but
//       // preceded by something blocking the header guard optimization.
//       if (!MI->isUsedForHeaderGuard())
//         Check->diag(MI->getDefinitionLoc(), "not header");
//       else
//         Check->diag(MI->getDefinitionLoc(), "aiya macro");
//     }

//     // Emit warnings for headers that are missing guards.
//     checkGuardlessHeaders();
//   }

  // void checkGuardlessHeaders() {
  //   // Look for header files that didn't have a header guard. Emit a warning and
  //   // fix-its to add the guard.
  //   // TODO: Insert the guard after top comments.
  //   for (const auto &FE : Files) {
  //     StringRef FileName = FE.getKey();
  //     if (!Check->shouldSuggestToAddHeaderGuard(FileName))
  //       continue;

  //     SourceManager &SM = PP->getSourceManager();
  //     FileID FID = SM.translateFile(FE.getValue());
  //     SourceLocation StartLoc = SM.getLocForStartOfFile(FID);
  //     if (StartLoc.isInvalid())
  //       continue;

  //     std::string CPPVar = Check->getHeaderGuard(FileName);
  //     std::string CPPVarUnder = CPPVar + '_'; // Allow a trailing underscore.
  //     // If there's a macro with a name that follows the header guard convention
  //     // but was not recognized by the preprocessor as a header guard there must
  //     // be code outside of the guarded area. Emit a plain warning without
  //     // fix-its.
  //     // FIXME: Can we move it into the right spot?
  //     bool SeenMacro = false;
  //     for (const auto &MacroEntry : Macros) {
  //       StringRef Name = MacroEntry.first.getIdentifierInfo()->getName();
  //       SourceLocation DefineLoc = MacroEntry.first.getLocation();
  //       if ((Name == CPPVar || Name == CPPVarUnder) &&
  //           SM.isWrittenInSameFile(StartLoc, DefineLoc)) {
  //         Check->diag(DefineLoc, "code/includes outside of area guarded by "
  //                                "header guard; consider moving it");
  //         SeenMacro = true;
  //         break;
  //       }
  //     }

  //     if (SeenMacro)
  //       continue;

  //     Check->diag(StartLoc, "header is missing header guard")
  //         << FixItHint::CreateInsertion(
  //                StartLoc, "#ifndef " + CPPVar + "\n#define " + CPPVar + "\n\n")
  //         << FixItHint::CreateInsertion(
  //                SM.getLocForEndOfFile(FID),
  //                Check->shouldSuggestEndifComment(FileName)
  //                    ? "\n#" + Check->formatEndIf(CPPVar) + "\n"
  //                    : "\n#endif\n");
  //   }
  // }

// private:
//   llvm::StringMap<const FileEntry *> Files;
//   std::vector<std::pair<Token, const MacroInfo *>> Macros;
//   ClangTidyCheck *Check;
//   Preprocessor *PP;
// };
// } // namespace



// void PreprocessorUsageCheck::registerPPCallbacks(
//     const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
//   PP->addPPCallbacks(
//       ::std::make_unique<PreprocessorUsageCallbacks>(this, PP));
// }


// bool PreprocessorUsageCheck::shouldSuggestToAddHeaderGuard(StringRef FileName) {
//   return utils::isFileExtension(FileName, HeaderFileExtensions);
// }
// bool PreprocessorUsageCheck::shouldSuggestEndifComment(StringRef FileName) {
//   return utils::isFileExtension(FileName, HeaderFileExtensions);
// }
// std::string PreprocessorUsageCheck::formatEndIf(StringRef HeaderGuard) {
//   return "endif // " + HeaderGuard.str();
// }


} // namespace bsl
} // namespace tidy
} // namespace clang
