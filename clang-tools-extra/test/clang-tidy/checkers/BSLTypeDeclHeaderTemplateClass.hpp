// RUN: %check_clang_tidy %s bsl-type-decl-header %t

template <typename T> class BSLTypeDeclHeaderTemplateClass {
  T foo;
}; // Compliant

template <typename T>
class NotBSLTypeDeclHeaderTemplateClass {}; // Non-compliant
// CHECK-MESSAGES: [[@LINE-1]]:7: warning: declared type name NotBSLTypeDeclHeaderTemplateClass does not have same name as header file BSLTypeDeclHeaderTemplateClass [bsl-type-decl-header]

namespace n1 {
template <typename T> class BSLTypeDeclHeaderTemplateClass {
  T foo;
  class Inner { // Compliant
    T innerfoo;
  };

  template <typename Y> class InnerTemplate { // Compliant
    Y innerfoo;
  };
}; // Compliant

template <typename T>
class NotBSLTypeDeclHeaderTemplateClass {}; // Non-compliant
// CHECK-MESSAGES: [[@LINE-1]]:7: warning: declared type name NotBSLTypeDeclHeaderTemplateClass does not have same name as header file BSLTypeDeclHeaderTemplateClass [bsl-type-decl-header]
} // namespace n1