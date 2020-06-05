set(LLVM_LINK_COMPONENTS support)

add_clang_library(clangTidyBslTestModule
  BslTestTidyModule.cpp
  BitwiseTypeCheck.cpp
  CastSignednessCheck.cpp

  LINK_LIBS
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangTidy
  clangTidyUtils
  )
