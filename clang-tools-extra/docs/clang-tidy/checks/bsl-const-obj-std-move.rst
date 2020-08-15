.. title:: clang-tidy - bsl-const-obj-std-move

bsl-const-obj-std-move
======================

Warns if std::move (or bsl::move) is used on objects declared const or const&.

Example:

.. code-block:: c++

  class A {
  };

  void f1() {
    const A a1{};
    A a2 = a1;            	// Compliant - copy constructor is called
    A a3 = std::move(a1); 	// Non-compliant

    A a4{};
    A a5 = std::move(a4);	// Compliant

    const A &a6{};
    A a7 = std::move(a6);	// Non-compliant
  }

  void f2() {
    const A a1{};
    A a2 = a1;            	// Compliant - copy constructor is called
    A a3 = bsl::move(a1); 	// Non-compliant

    A a4{};
    A a5 = bsl::move(a4);	// Compliant

    const A &a6{};
    A a7 = bsl::move(a6);	// Non-compliant
  }

