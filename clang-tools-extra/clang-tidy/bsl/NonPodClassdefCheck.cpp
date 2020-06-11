//===--- NonPodClassdefCheck.cpp - clang-tidy -----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NonPodClassdefCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

// AST_MATCHER(CXXRecordDecl, hasVirtualBases) {
//   CXXRecordDecl *Def = Node.getDefinition();
//   return Def->getNumVBases() > 0;
// }

void NonPodClassdefCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(cxxRecordDecl(has(accessSpecDecl(anyOf(isPublic(), isProtected())))).bind("private"), this);  // cxxRecordDecl
  // Finder->addMatcher(fieldDecl(unless(isPrivate())).bind("private"), this);

  Finder->addMatcher(cxxRecordDecl(hasDefinition(), unless(isClass())).bind("class"), this);
  // enums are PODs

  // Finder->addMatcher(tagDecl(isStruct(), ));
  // fieldDecl(isPublic())
  // hasAnyBase()
  // check other classes and struct: check base not isStruct()
  
    // Finder->addMatcher(cxxBaseSpecifier(isVirtual()))
  // trivial
  // Finder->addMatcher(decl(anyOf(cxxRecordDecl(hasDefinition(), hasVirtualBases()),
  //           cxxMethodDecl(isVirtual())
  //           )).bind("class"), this);

  // cxxConstructorDecl(anyOf(isMoveConstructor(), isCopyConstructor()))
  // unless(cxxConstructorDecl(isDefaultConstructor()), cxxDestructorDecl(isDefaulted()))  // no ConstructorDecl

  // // standard layout
  // functionDecl(isStaticStorageClass()), unless(standard layout??)
  // varDecl(isStaticStorageClass()), unless(standard layout??)

  /* 1. Check if not trivially copyable: has virtual anything, has non-default constructor
     2. Check not standard-layout: has static data, not "same access control," at most one base class subobject
     3. If not either one (ie, not POD):
         1. match if not a class (ie, if union, struct, typedef, etc)
         2. match if memberdata not isPrivate, ie isProtected, isPublic, or isVirtual
     4. If POD, do nothing
     5. but if POD struct, check 1-4
  */
  // don't need to check for static
  // hasInClassInitializer, isClass, but vars not isPrivate, ie isProtected, isPublic, or isVirtual

  // or isStruct that does not satisfy (1)-(4), ie has non-public data, has funcions, is a base class, or inherits from something

  // but if POD class type not struct, ignore (class with no constructor?)
}

void NonPodClassdefCheck::check(const MatchFinder::MatchResult &Result) {
  // member data
  auto Var = Result.Nodes.getNodeAs<CXXRecordDecl>("private");
  if (Var) {
      auto Loc = Var->getLocation();
    if (Loc.isInvalid() || Loc.isMacroID())
      return;

    auto Mgr = Result.SourceManager;
    if (Mgr->getFileID(Loc) != Mgr->getMainFileID())
      return;

    if (Var->isPOD())
      return;
    else
      diag(Loc, "non-POD class types should have private member data");
  }

  // class type
  auto NonPodClass = Result.Nodes.getNodeAs<CXXRecordDecl>("class");

  if (NonPodClass) {
    auto PodLoc = NonPodClass->getLocation();

    if (NonPodClass->isPOD())
      return;
    else
      diag(PodLoc, "non-POD type should be defined as a class");
  }

}

} // namespace bsl
} // namespace tidy
} // namespace clang
