.. title:: clang-tidy - bsl-function-noexcept

bsl-function-noexcept
=====================

Checks that every function is marked as noexcept or noexcept(false).
Note: noexcept(true) accepted

Examples:

.. code-block:: c++

  void f1();
  void f2() noexcept;
  void f3() noexcept(true);
  void f4() noexcept(false);
  void f5() noexcept {
    try {
      f1();
    } catch (std::exception &e) {
    }

    f2();
    f3();

    try {
      f4();
    } catch (std::exception &e) {
    }
  }

  template <class T> void f6() noexcept(noexcept(T()));

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
  };

