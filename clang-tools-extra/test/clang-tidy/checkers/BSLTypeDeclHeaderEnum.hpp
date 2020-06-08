// RUN: %check_clang_tidy %s bsl-type-decl-header %t

enum BSLTypeDeclHeaderEnum { x, y, z }; // Compliant

enum NotBSLTypeDeclHeaderEnum { a, b, c }; // Non-compliant
// CHECK-MESSAGES: [[@LINE-1]]:6: warning: declared type name NotBSLTypeDeclHeaderEnum does not have same name as header file BSLTypeDeclHeaderEnum [bsl-type-decl-header]

namespace n1 {
enum BSLTypeDeclHeaderEnum { u, v, w }; // Compliant

enum NotBSLTypeDeclHeaderEnum { i, j, k }; // Non-compliant
// CHECK-MESSAGES: [[@LINE-1]]:6: warning: declared type name NotBSLTypeDeclHeaderEnum does not have same name as header file BSLTypeDeclHeaderEnum [bsl-type-decl-header]
} // namespace n1