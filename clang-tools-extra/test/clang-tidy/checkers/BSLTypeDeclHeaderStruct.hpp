// RUN: %check_clang_tidy %s bsl-type-decl-header %t

struct BSLTypeDeclHeaderStruct { // Compliant
  int x;
};

struct NotBSLTypeDeclHeaderStruct {}; // Non-compliant
// CHECK-MESSAGES: [[@LINE-1]]:8: warning: declared type name NotBSLTypeDeclHeaderStruct does not have same name as header file BSLTypeDeclHeaderStruct [bsl-type-decl-header]

namespace n1 {
struct BSLTypeDeclHeaderStruct { // Compliant
  int x;
  struct Inner {}; // Compliant
};

struct NotBSLTypeDeclHeaderStruct {}; // Non-compliant
// CHECK-MESSAGES: [[@LINE-1]]:8: warning: declared type name NotBSLTypeDeclHeaderStruct does not have same name as header file BSLTypeDeclHeaderStruct [bsl-type-decl-header]
} // namespace n1