// RUN: %check_clang_tidy %s bsl-forward-reference-overloaded %t

template <typename T> void f1(T &&t) {}

// Overloading a function with forwarding reference
void f1(int &&t) {} // Non-compliant
// CHECK-MESSAGES: [[@LINE-1]]:6: warning: function f1 overloads function declaration with forwarding reference on line 3 [bsl-forward-reference-overloaded]

void f1(int x, int &&t) {} // Compliant

template <typename T> void f1(T &&t, int a, int b) {} // Compliant

template <typename T> void f2(T &&t) {}

void f2(int &) = delete; // Compliant by exception

template <typename T> void f3(T &&t, int a, int b) {} // Compliant

template <typename T>
void f3(T &&t, T &&y, int b) {} // Non-compliant, same number of params
// CHECK-MESSAGES: [[@LINE-1]]:6: warning: function f3 overloads function declaration with forwarding reference on line 17 [bsl-forward-reference-overloaded]

class A {
  template <typename T> void f1(T &&t) {}

  void f1(int &&t) {} // Non-compliant
  // CHECK-MESSAGES: [[@LINE-1]]:8: warning: function A::f1 overloads function declaration with forwarding reference on line 24 [bsl-forward-reference-overloaded]

  template <typename T> void f2(T &&t) {}

  void f2(int &) = delete; // Compliant by deletion

  // Ignore move and copy
  A( const A& other);
  A& operator=(const A& other);
  A(A&& other);
  A& operator=(A&& other);
};

// Not forward references
void f4(A &&a) {}

void f4(int &) = delete; // Compliant

void f5(A &&a) {}

void f5(int &&a) {} // Compliant

namespace n1 {
void f1(int &&t) {} // Non-compliant with f1(T &&t)
// CHECK-MESSAGES: [[@LINE-1]]:6: warning: function n1::f1 overloads function declaration with forwarding reference on line 55 [bsl-forward-reference-overloaded]

void f1(int x, int &&t) {} // Compliant

template <typename T> void f1(T &&t) {}

void f1(long &&t) {} // Non-compliant with f1(T &&t)
// CHECK-MESSAGES: [[@LINE-1]]:6: warning: function n1::f1 overloads function declaration with forwarding reference on line 55 [bsl-forward-reference-overloaded]

template <typename T> void f1(T &&t, int a, int b) {} // Compliant

template <typename T> void f2(T &&t) {}

void f2(int &) = delete; // Compliant by deletion

template <typename T> void f3(T &&t, int a, int b) {} // Compliant

template <typename T>
void f3(T &&t, T &&y, int b) {} // Non-compliant, same number of params
// CHECK-MESSAGES: [[@LINE-1]]:6: warning: function n1::f3 overloads function declaration with forwarding reference on line 66 [bsl-forward-reference-overloaded]
} // namespace n1