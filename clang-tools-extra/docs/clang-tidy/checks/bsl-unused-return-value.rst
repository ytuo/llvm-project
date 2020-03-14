.. title:: clang-tidy - bsl-unused-return-value

bsl-unused-return-value
=======================

Emits a warning whenever a non-void function return
value is ignored, unless the function is an overloaded
C++ operator or it is explicitly ignored with
static_cast<void>().

Examples:

.. code-block:: c++

  int foo()
  {
    return 1;
  }

  void bar()
  {
    // No warning
    auto x = foo();

    // Warning
    foo();

    // No warning
    static_cast<void>(foo());
  }
