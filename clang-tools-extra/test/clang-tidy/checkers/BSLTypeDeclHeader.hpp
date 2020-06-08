// RUN: %check_clang_tidy %s bsl-type-decl-header %t
// When running check_clang_tidy script, make sure that temp file name is test file name
// ie, BSLTypeDeclHeader for this test

// All compliant
namespace n1 {
// Function
int BSLTypeDeclHeader(){};
void foo(){};
long bar = 0;
} // namespace n1

namespace n2 {
// Type alias
using BSLTypeDeclHeader = void;
using bar = void;
} // namespace n2

namespace n3 {
// Template type alias
template <class T> using BSLTypeDeclHeader = T *;

template <class T> using foo = T *;
} // namespace n3

namespace n4 {
class BSLTypeDeclHeader {
  struct Inner {};

  union InnerUnion {
    enum InnerEnum { a };
  };
};
} // namespace n4

namespace n5 {
template <typename T> struct BSLTypeDeclHeader {
  T foo;
  struct Inner {
    T innerfoo;
  };

  template <typename Y> struct InnerTemplate { Y innerfoo; };
}; // Compliant
} // namespace n5

class C {
  struct Inner {};

  union InnerUnion {
    enum InnerEnum { a };
  };
};
// CHECK-MESSAGES: [[@LINE-7]]:7: warning: declared type name C does not have same name as header file BSLTypeDeclHeader [bsl-type-decl-header]

template <typename T> struct S {
  T foo;
  struct Inner {
    T innerfoo;
  };

  template <typename Y> struct InnerTemplate { Y innerfoo; };
};
// CHECK-MESSAGES: [[@LINE-8]]:30: warning: declared type name S does not have same name as header file BSLTypeDeclHeader [bsl-type-decl-header]
