//===--- UsingIdentUniqueNamespaceCheck.cpp - clang-tidy ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "UsingIdentUniqueNamespaceCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bsl {

void UsingIdentUniqueNamespaceCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(typeAliasDecl().bind("using"), this);
  Finder->addMatcher(tagDecl(anyOf(
                      cxxRecordDecl(hasDefinition()),
                      enumDecl()
                      )).bind("tag"), this);
  // typedef?
}


// use lookup stuff at each level?
void UsingIdentUniqueNamespaceCheck::check(
    const MatchFinder::MatchResult &Result) {
  auto Mgr = Result.SourceManager;

  // version 2 use lookups
  // const auto *D = Result.Nodes.getNodeAs<TypeAliasDecl>("using");
  // if (D) {
    
  //   const auto Loc = D->getBeginLoc();
  //   if (Loc.isInvalid())
  //     return;    

  //   std::string name = D->getNameAsString();
  //   const DeclContext *ns = D->getDeclContext();
  //   auto *curns = ns;

  //   while (curns) {
  //     // check if parent is class, not namespace (lexicalparent?)
  //     // for (NamedDecl *item : curns->lookup(name)) {
  //     //   // unless namespace unnamed? 
  //     //   if (item == D) {
  //     //     unsigned int locnum = Mgr->getPresumedLoc(item).getLine();
  //     //     diag(Loc, "%0 already used in %1 at line %2")
  //     //         << name << curns << locnum;
  //     //   }
  //     // }
  //     diag(Loc, "%0") << D->getDeclName();
  //     if (curns->lookup(D->getDeclName()).size() > 1) {
  //        diag(Loc,"more than one");
  //     }
          
  //     curns = curns->getLexicalParent();
  //   }
  // }
  

  // const auto *MatchedDecl = Result.Nodes.getNodeAs<TagDecl>("tag");
  // if (MatchedDecl) {
  //   const auto Loc = MatchedDecl->getBeginLoc();
  //   if (Loc.isInvalid())
  //     return;

  //   std::string name = MatchedDecl->getNameAsString();
  //   const DeclContext *ns = MatchedDecl->getDeclContext();
  //   auto *curns = ns;

  //   while (curns) {
  //   // check if parent is class, not namespace (lexicalparent?)
  //     // for (NamedDecl *item : curns->lookup(name)) {
  //     //   // unless namespace unnamed? 
  //     //   if (item == D) {
  //     //     unsigned int locnum = Mgr->getPresumedLoc(item).getLine();
  //     //     diag(Loc, "%0 already used in %1 at line %2")
  //     //         << name << curns << locnum;
  //     //   }
  //     // }
  //     diag(Loc, "%0") << MatchedDecl->getDeclName();
  //     if (curns->lookup(MatchedDecl->getDeclName()).size() > 1) {
  //        diag(Loc,"more than one");
  //     }
          
  //     curns = curns->getLexicalParent();
  //   }
  // }

  // version 1
// // getOuterLexicalRecordContext ()
// const auto *D = Result.Nodes.getNodeAs<TypeAliasDecl>("using");
//   if (D) {
//     const auto Loc = D->getBeginLoc();
//     if (Loc.isInvalid())
//       return;

//     std::string name = D->getNameAsString();
//     const DeclContext *ns = D->getDeclContext();  //->getEnclosingNamespaceContext();
//     auto *curns = ns;

//     bool seen = false;
//     while (curns) {
//       if (curns->isRecord()) {
//         diag(Loc, "is record");
//       }

//        if (curns->getOuterLexicalRecordContext()) {
//         diag(Loc, "lexical %0") << curns->getOuterLexicalRecordContext()->getName() ;
//       }
//       // diag(Loc, "parent: %0, lexical parent: %1, lookup parent: %2")
//       //   << curns->getParent() << curns->getLexicalParent() << curns->getLookupParent();

//       diag(Loc, "%0 already used in %1 declkind %2")
//               << name << curns << curns->getDeclKindName();
//       curns = curns->getLexicalParent();
//     }
//   }
  

//   const auto *MatchedDecl = Result.Nodes.getNodeAs<TagDecl>("tag");
//   if (MatchedDecl) {
//     const auto Loc = MatchedDecl->getBeginLoc();
//     if (Loc.isInvalid())
//       return;

//     std::string name = MatchedDecl->getNameAsString();
//     const DeclContext *ns = MatchedDecl->getDeclContext();  //->getEnclosingNamespaceContext(); // getLexicalDeclContext
//     auto *curns = ns;

//     bool seen = false;
//     while (curns) {
//       if (curns->isRecord()) {
//         diag(Loc, "derp");
//       }
//       if (curns->getOuterLexicalRecordContext()) {
//         diag(Loc, "lexical %0") << curns->getOuterLexicalRecordContext()->getName() ;
//       }

//       // diag(Loc, "parent: %0, lexical parent: %1, lookup parent: %2")
//       //   << curns->getParent() << curns->getLexicalParent() << curns->getLookupParent();


//       diag(Loc, "%0 already used in %1 declkind %2")
//               << name << curns << curns->getDeclKindName();
//       curns = curns->getLexicalParent();
//     }
//   }




  const auto *D = Result.Nodes.getNodeAs<TypeAliasDecl>("using");
  if (D) {
    
    const auto Loc = D->getBeginLoc();
    if (Loc.isInvalid())
      return;
  //   if (D->isCXXClassMember()) {
  //     diag(Loc, "yes");
  //   } else {
  //     diag(Loc, "no");
  //   }

  // }
    // is Record?()
    

    std::string name = D->getNameAsString();
    const DeclContext *ns = D->getDeclContext();  //->getEnclosingNamespaceContext();
    auto *curns = ns;

    bool seen = false;
    while (curns) {
      // check if parent is class, not namespace (lexicalparent?)
      auto itr = namespaceToIDs.find(curns);
      if (itr != namespaceToIDs.end()) {
        auto id_itr = (itr->second).find(name);
        if (id_itr != (itr->second).end()) {
          unsigned int locnum = Mgr->getPresumedLoc(id_itr->second).getLine();
          diag(Loc, "%0 already used in %1 at line %2")
              << name << curns->getEnclosingNamespaceContext() << locnum;
          seen = true;
          break;
        } else if (curns == ns) { // technically should only add at end, would cause more collisions
          (itr->second)[name] = Loc;
        }

      } else if (curns == ns) {
        namespaceToIDs[curns] = {{name, Loc}};
      }
      // curns = curns->getParent(); // if curns isTranslationUnit, parent is null
      curns = curns->getLexicalParent();
    }
  }
  

  const auto *MatchedDecl = Result.Nodes.getNodeAs<TagDecl>("tag");
  if (MatchedDecl) {
    const auto Loc = MatchedDecl->getBeginLoc();
    if (Loc.isInvalid())
      return;

    std::string name = MatchedDecl->getNameAsString();
    const DeclContext *ns = MatchedDecl->getDeclContext(); //->getEnclosingNamespaceContext();
    auto *curns = ns;

    bool seen = false;
    while (curns) {
      auto itr = namespaceToIDs.find(curns);
      if (itr != namespaceToIDs.end()) {
        auto id_itr = (itr->second).find(name);
        if (id_itr != (itr->second).end()) {
          // check if class
          unsigned int locnum = Mgr->getPresumedLoc(id_itr->second).getLine();
          diag(Loc, "%0 already used in %1 at line %2")
              << name << curns->getEnclosingNamespaceContext() << locnum;
          seen = true;
          break;
        } else if (curns == ns) {
          (itr->second)[name] = Loc;
        }

      } else if (curns == ns) {
        namespaceToIDs[curns] = {{name, Loc}};    // map name to class and loc
        // curns is declcontext, is parent class also declcontext? simply add class as ns
      }
      // curns = curns->getParent(); // if isTranslationUnit, curns parent is null
      curns = curns->getLexicalParent();
    }
  }


}

} // namespace bsl
} // namespace tidy
} // namespace clang
