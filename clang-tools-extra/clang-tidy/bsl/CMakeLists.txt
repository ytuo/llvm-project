set(LLVM_LINK_COMPONENTS support)

add_clang_library(clangTidyBslModule
  BslCheckUtils.cpp
  BslTidyModule.cpp
  EnumExplicitCheck.cpp
  EnumInitCheck.cpp
  EnumScopedCheck.cpp
  LambdaImplicitCaptureCheck.cpp
  LambdaParamListCheck.cpp
  LiteralsAsciiOnlyCheck.cpp
  LiteralsNoOctalCheck.cpp
  LiteralsUnsignedSuffixCheck.cpp
  LiteralsUppercaseSuffixCheck.cpp
  NonPodStaticCheck.cpp
  OpForbiddenOverloadCheck.cpp
  TypesFixedWidthIntsCheck.cpp
  TypesNoWideCharCheck.cpp
  UnusedReturnValueCheck.cpp

  LINK_LIBS
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangTidy
  clangTidyUtils
  )
