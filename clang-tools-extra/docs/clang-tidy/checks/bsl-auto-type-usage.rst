.. title:: clang-tidy - bsl-auto-type-usage

bsl-auto-type-usage
===================

Checks that the auto specifier is only used
 (1) to declare that a variable has the same type as return type of a function call
 (2) to declare that a variable has the same type as initializer of non-fundamental type
 (3) to declare parameters of a generic lambda expression
 (4) to declare a function (template) using trailing return type syntax.
Note: literal types (except strings) and list initializers are not allowed

Examples:

.. code-block:: c++

  class A {};

  void f1() noexcept {
    auto x1 = 5; // Non-compliant
    auto x2 = 0.3F; // Non-compliant
    auto x3 = {8}; // Non-compliant
    std::vector<int> v;
    auto x4 = v.size(); // Compliant with case (1) - x4 is of size_t type that is returned from v.size() method
    auto a = A{};       // Compliant with case (2)
    auto lambda1 = []() -> int {
      return 5U;
    }; // Compliant with case (2) - lambda1 is of non-fundamental lambda expression type
    auto x5 = lambda1(); // Compliant with case (1)
    auto x7 = std::initializer_list<int>{3}; // Non-compliant
    auto x8 = 'c'; // Non-compliant
    auto x9 = "hello";
    auto x10 = 0xbeef; // Non-compliant
    auto x11 = 5l; // Non-compliant
    auto x12 = 6ul; // Non-compliant
    auto x13 = 0123; // Non-compliant
    auto x14 = 27182e-4; // Non-compliant
    auto x15 = true; // Non-compliant
  }

  void f2() noexcept {
    auto lambda1 = [](auto x, auto y) -> decltype(x + y) {
      return (x + y);
    };                          // Compliant with cases (2) and (3)
    auto y1 = lambda1(5.0, 10); // Compliant with case (1)
  }

  template <typename T, typename U>
  auto f3(T t, U u) noexcept -> decltype(t + u) // Compliant with case (4)
  {
    return (t + u);
  }

  auto f4() -> auto { // Not allowed; no non-auto trailing return
    return 3;
  }

  auto f5(int x, int y) -> int
  {
    return x + y;
  }

  auto f6(int x, int y) // Non-compliant; no trailing return
  {
    return x + y;
  }

  template <typename T> 
  class B {
  public:
    T fn(T t);
  };

  template <typename T>
  auto B<T>::fn(T t) -> T // Compliant with case (4)
  {
    return t;
  }
