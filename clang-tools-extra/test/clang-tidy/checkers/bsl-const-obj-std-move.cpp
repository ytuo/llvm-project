// RUN: %check_clang_tidy %s bsl-const-obj-std-move %t

// Manually define remove_reference
template <class T> struct remove_reference { typedef T type; };

template <class T> struct remove_reference<T &> { typedef T type; };

template <class T> struct remove_reference<T &&> { typedef T type; };

template <class T>
using remove_reference_t = typename remove_reference<T>::type;

namespace std {
// Manually define std::move
template <typename T> constexpr remove_reference_t<T> &&move(T &&val) noexcept {
  return static_cast<remove_reference_t<T> &&>(val);
}
} // namespace std

namespace bsl {
// Manually define bsl::move
template <typename T> constexpr remove_reference_t<T> &&move(T &&val) noexcept {
  return static_cast<remove_reference_t<T> &&>(val);
}
} // namespace bsl

class A {};

void f1() {
  const A a1{};
  A a2 = a1;            // Compliant - copy constructor is called
  A a3 = std::move(a1); // Non-compliant
  // CHECK-MESSAGES: :[[@LINE-1]]:10: warning: invoking std::move with const argument a1 [bsl-const-obj-std-move]
  // CHECK-MESSAGES: :[[@LINE-4]]:3: note: argument a1 declared const here
  A a4{};
  A a5 = std::move(a4); // Compliant

  const A &a6{};
  A a7 = std::move(a6); // Non-compliant
  // CHECK-MESSAGES: :[[@LINE-1]]:10: warning: invoking std::move with const argument a6 [bsl-const-obj-std-move]
  // CHECK-MESSAGES: :[[@LINE-3]]:3: note: argument a6 declared const here
}

void f2() {
  const A a1{};
  A a2 = a1;            // Compliant - copy constructor is called
  A a3 = bsl::move(a1); // Non-compliant
  // CHECK-MESSAGES: :[[@LINE-1]]:10: warning: invoking bsl::move with const argument a1 [bsl-const-obj-std-move]
  // CHECK-MESSAGES: :[[@LINE-4]]:3: note: argument a1 declared const here
  A a4{};
  A a5 = bsl::move(a4); // Compliant

  const A &a6{};
  A a7 = bsl::move(a6); // Non-compliant
  // CHECK-MESSAGES: :[[@LINE-1]]:10: warning: invoking bsl::move with const argument a6 [bsl-const-obj-std-move]
  // CHECK-MESSAGES: :[[@LINE-3]]:3: note: argument a6 declared const here
}

// Compliant; ignore other namespaces
namespace foo {
// Manually define foo::move
template <typename T> constexpr remove_reference_t<T> &&move(T &&val) noexcept {
  return static_cast<remove_reference_t<T> &&>(val);
}
} // namespace foo

void f5() {
  const A a1{};
  A a2 = a1;
  A a3 = foo::move(a1);
  A a4{};
  A a5 = foo::move(a4);

  const A &a6{};
  A a7 = foo::move(a6);
}

namespace other {
A move(A a) { return A(); }
} // namespace other

void f3() {
  const A a1{};
  A a2 = a1;
  A a3 = other::move(a1);

  A a4{};
  A a5 = other::move(a4);

  const A &a6{};
  A a7 = other::move(a6);
}

A move(A a) { return A(); }

void f4() {
  const A a1{};
  A a2 = a1;
  A a3 = move(a1);

  A a4{};
  A a5 = move(a4);

  const A &a6{};
  A a7 = move(a6);
}
