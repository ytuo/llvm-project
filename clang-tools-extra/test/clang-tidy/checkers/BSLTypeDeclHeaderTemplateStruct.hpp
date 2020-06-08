// RUN: %check_clang_tidy %s bsl-type-decl-header %t

template <typename T> struct BSLTypeDeclHeaderTemplateStruct {
  T foo;
}; // Compliant

template <typename T>
struct NotBSLTypeDeclHeaderTemplateStruct {}; // Non-compliant
// CHECK-MESSAGES: [[@LINE-1]]:8: warning: declared type name NotBSLTypeDeclHeaderTemplateStruct does not have same name as header file BSLTypeDeclHeaderTemplateStruct [bsl-type-decl-header]
namespace n1 {
template <typename T> struct BSLTypeDeclHeaderTemplateStruct {
  T foo;
  struct Inner { // Compliant
    T innerfoo;
  };

  template <typename Y> struct InnerTemplate { // Compliant
    Y innerfoo;
  };
}; // Compliant

template <typename T>
struct NotBSLTypeDeclHeaderTemplateStruct {}; // Non-compliant
// CHECK-MESSAGES: [[@LINE-1]]:8: warning: declared type name NotBSLTypeDeclHeaderTemplateStruct does not have same name as header file BSLTypeDeclHeaderTemplateStruct [bsl-type-decl-header]
} // namespace n1