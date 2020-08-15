// RUN: %check_clang_tidy %s bsl-auto-type-usage %t
// RUN: -std=c++14

namespace std {
  template<typename T>
  class initializer_list{};

  typedef int size_t;

  template <class T>
  class vector {
  public:
    size_t size();
  };
}

class A {};

void f1() noexcept {
  auto x1 = 5;
  // CHECK-MESSAGES: :[[@LINE-1]]:8: warning: auto cannot be used to declare variable of fundamental type [bsl-auto-type-usage] 
  auto x2 = 0.3F;
  // CHECK-MESSAGES: :[[@LINE-1]]:8: warning: auto cannot be used to declare variable of fundamental type [bsl-auto-type-usage]
  auto x3 = {8};
  // CHECK-MESSAGES: :[[@LINE-1]]:8: warning: auto cannot be used for list initializers [bsl-auto-type-usage]

  std::vector<int> v;
  auto x4 = v.size(); // Compliant with case (1) - x4 is of size_t type that is returned from v.size() method
  auto a = A{};       // Compliant with case (2)
  auto lambda1 = []() -> int {
    return 5U;
  }; // Compliant with case (2) - lambda1 is of non-fundamental lambda expression type
  auto x5 = lambda1(); // Compliant with case (1)
  auto x7 = std::initializer_list<int>{3}; // non-compliant
  // CHECK-MESSAGES: :[[@LINE-1]]:8: warning: auto cannot be used for list initializers [bsl-auto-type-usage]

  auto x8 = 'c';
  // CHECK-MESSAGES: :[[@LINE-1]]:8: warning: auto cannot be used to declare variable of fundamental type [bsl-auto-type-usage]
  auto x9 = "hello";
  auto x10 = 0xbeef;
  // CHECK-MESSAGES: :[[@LINE-1]]:8: warning: auto cannot be used to declare variable of fundamental type [bsl-auto-type-usage]
  auto x11 = 5l;
  // CHECK-MESSAGES: :[[@LINE-1]]:8: warning: auto cannot be used to declare variable of fundamental type [bsl-auto-type-usage]
  auto x12 = 6ul;
  // CHECK-MESSAGES: :[[@LINE-1]]:8: warning: auto cannot be used to declare variable of fundamental type [bsl-auto-type-usage]
  auto x13 = 0123;
  // CHECK-MESSAGES: :[[@LINE-1]]:8: warning: auto cannot be used to declare variable of fundamental type [bsl-auto-type-usage]
  auto x14 = 27182e-4;
  // CHECK-MESSAGES: :[[@LINE-1]]:8: warning: auto cannot be used to declare variable of fundamental type [bsl-auto-type-usage]
  auto x15 = true;
  // CHECK-MESSAGES: :[[@LINE-1]]:8: warning: auto cannot be used to declare variable of fundamental type [bsl-auto-type-usage]
}

void f2() noexcept {
  auto lambda1 = [](auto x, auto y) -> decltype(x + y) {
    return (x + y);
  };                          // Compliant with cases (2) and (3)
  auto y1 = lambda1(5.0, 10); // Compliant with case (1)
}

template <typename T> class B {
public:
  T fn(T t);
};

template <typename T>
auto B<T>::fn(T t) -> T // Compliant with case (4)
{
  return t;
}

template <typename T> class C {
  auto fn(int x, int y)
      -> int;
public:
  T fn(T t);
};

template <typename U>
auto C<U>::fn(U u) -> U // Compliant
{
  return u;
}

template <typename T, typename U>
auto f3(T t, U u) noexcept -> decltype(t + u) // Compliant with case (4)
{
  return (t + u);
}

auto f4(); // Non-compliant; no trailing return
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: auto can only be used for declaring function templates with a trailing return [bsl-auto-type-usage]

auto f5() { // Non-compliant; no trailing return
  return 3;
}
// CHECK-MESSAGES: :[[@LINE-3]]:6: warning: auto can only be used for declaring function templates with a trailing return [bsl-auto-type-usage]

auto f6() -> auto { // Not allowed; no non-auto trailing return
  return 3;
}
// CHECK-MESSAGES: :[[@LINE-3]]:6: warning: auto can only be used for declaring function templates with a trailing return [bsl-auto-type-usage]

auto f7(int x, int y) -> int
{
  return x + y;
}

auto f8(int x, int y) // Non-compliant; no trailing return
{
  return x + y;
}
// CHECK-MESSAGES: :[[@LINE-4]]:6: warning: auto can only be used for declaring function templates with a trailing return [bsl-auto-type-usage]

template <typename T>
auto f9(T x, T y) -> T; // Compliant

// Supported in c++ 20
// void f4(auto x)
// {
// }