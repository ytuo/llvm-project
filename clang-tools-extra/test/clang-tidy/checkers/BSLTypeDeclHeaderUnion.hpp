// RUN: %check_clang_tidy %s bsl-type-decl-header %t

union BSLTypeDeclHeaderUnion { // Compliant
  int x;
};

union NotBSLTypeDeclHeaderUnion {}; // Non-compliant
// CHECK-MESSAGES: [[@LINE-1]]:7: warning: declared type name NotBSLTypeDeclHeaderUnion does not have same name as header file BSLTypeDeclHeaderUnion [bsl-type-decl-header]

namespace n1 {
union BSLTypeDeclHeaderUnion { // Compliant
  int x;
  union Inner {}; // Compliant
};

union NotBSLTypeDeclHeaderUnion {}; // Non-compliant
// CHECK-MESSAGES: [[@LINE-1]]:7: warning: declared type name NotBSLTypeDeclHeaderUnion does not have same name as header file BSLTypeDeclHeaderUnion [bsl-type-decl-header]
} // namespace n1