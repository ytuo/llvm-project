// RUN: %check_clang_tidy %s bsl-type-decl-header %t

typedef struct {
  int a;
  int b;
} BSLTypeDeclHeaderTypedef; // Compliant

typedef long NotBSLTypeDeclHeaderTypedef; // Non-compliant
// CHECK-MESSAGES: [[@LINE-1]]:7: warning:

void foo() {
  typedef int foo; // Compliant
}

template <typename T> struct S {
  typedef const T foo; // Compliant
};
// CHECK-MESSAGES: [[@LINE-1]]:7: warning:

template <typename T> class C {
  typedef long foo; // Compliant
};
// CHECK-MESSAGES: [[@LINE-1]]:7: warning:

namespace n1 {
typedef struct {
  int a;
  int b;
} BSLTypeDeclHeaderTypedef; // Compliant

typedef long NotBSLTypeDeclHeaderTypedef; // Non-compliant
// CHECK-MESSAGES: [[@LINE-1]]:7: warning:
} // namespace n1

namespace n2 {
typedef void (*BSLTypeDeclHeaderTypedef)(int arg1); // Compliant

void foo(int x) {}

BSLTypeDeclHeaderTypedef ref = &foo;
} // namespace n2

namespace n3 {
template <typename T> struct BSLTypeDeclHeaderTypedef {
  typedef const T foo; // Compliant
};
} // namespace n3

namespace n4 {
template <typename T> class BSLTypeDeclHeaderTypedef {
  typedef long foo; // Compliant
};
} // namespace n4