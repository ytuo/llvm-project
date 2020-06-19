// RUN: %check_clang_tidy %s bsl-function-noexcept %t

void f1();
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: Every function should be marked as noexcept or noexcept(false) [bsl-function-noexcept]

void f2() noexcept;
void f3() noexcept(true);
void f4() noexcept(false);

template <class T> void f5() noexcept(noexcept(T()));

template <class T> class A {
public:
  A() noexcept(noexcept(T())) {} // Compliant
};

class C1 {
public:
  C1() noexcept(true) {} // Compliant
};

class C2 {
public:
  C2() {} // Non-compliant
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: Every function should be marked as noexcept or noexcept(false) [bsl-function-noexcept]
};
