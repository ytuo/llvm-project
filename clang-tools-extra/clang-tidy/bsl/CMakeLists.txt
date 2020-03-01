set(LLVM_LINK_COMPONENTS support)

add_clang_library(clangTidyBslModule
  BslTidyModule.cpp
  FixedWidthInts.cpp
  LiteralsNoOctalCheck.cpp
  LiteralsUnsignedSuffixCheck.cpp
  LiteralsUppercaseSuffixCheck.cpp

  LINK_LIBS
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangTidy
  clangTidyUtils
  )
