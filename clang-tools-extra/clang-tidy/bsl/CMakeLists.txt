set(LLVM_LINK_COMPONENTS support)

add_clang_library(clangTidyBslModule
  BslCheckUtils.cpp
  BslTidyModule.cpp
  LiteralsAsciiOnlyCheck.cpp
  LiteralsNoOctalCheck.cpp
  LiteralsUnsignedSuffixCheck.cpp
  LiteralsUppercaseSuffixCheck.cpp
  TypesFixedWidthIntsCheck.cpp

  LINK_LIBS
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangTidy
  clangTidyUtils
  )
