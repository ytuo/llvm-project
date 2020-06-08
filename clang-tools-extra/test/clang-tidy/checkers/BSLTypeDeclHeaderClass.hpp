// RUN: %check_clang_tidy %s bsl-type-decl-header %t

class BSLTypeDeclHeaderClass { // Compliant
  int foo;
};

class NotBSLTypeDeclHeaderClass {}; // Non-compliant
// CHECK-MESSAGES: [[@LINE-1]]:7: warning: declared type name NotBSLTypeDeclHeaderClass does not have same name as header file BSLTypeDeclHeaderClass [bsl-type-decl-header]

namespace n1 {
class BSLTypeDeclHeaderClass { // Compliant
  class Inner {};              // Compliant
};

class NotBSLTypeDeclHeaderClass {}; // Non-compliant
// CHECK-MESSAGES: [[@LINE-1]]:7: warning: declared type name NotBSLTypeDeclHeaderClass does not have same name as header file BSLTypeDeclHeaderClass [bsl-type-decl-header]
} // namespace n1