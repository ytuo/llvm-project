.. title:: clang-tidy - bsl-lambda-implicit-capture

bsl-lambda-implicit-capture
===========================

This check warns whenever variables with automatic storage
duration are implicitly captured by a lambda expression.

Examples:

.. code-block:: c++

  thread_local double c;

  void foo()
  {
      int a;
      static int b;

      // Warns on the line below
      auto f = [&](){ return a + b; };

      auto g = [=](){ return b; };
      auto h = [&](){ return c; };
      auto i = [a](){ return a * 2; };
      auto j = [&a](){ return a * 3; };
  }
