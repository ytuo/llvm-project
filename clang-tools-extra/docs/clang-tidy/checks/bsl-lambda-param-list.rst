.. title:: clang-tidy - bsl-lambda-param-list

bsl-lambda-param-list
=====================

This check warns whenever parameter lists are not
explicitly listed in lambda expressions.

Examples:

.. code-block:: c++

  void foo()
  {
      // Warns on the line below
      auto f = []{ return 0; };

      // No warnings here
      auto g = [](){ return 0; };
      auto h = [](int x){ return x * x; };
  }
