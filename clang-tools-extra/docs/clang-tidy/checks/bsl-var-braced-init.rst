.. title:: clang-tidy - bsl-var-braced-init

bsl-var-braced-init
===================

This check warns whenever direct list initialization is not used for
non-auto-declared variables. Also warns whenever any list initialization
is used for auto-declared variables.

Examples:

.. code-block:: c++

  #include <initializer_list>

  template<typename T>
  void f(T t)
  {
      // Warns on x and t0
      int x = 4;
      T t0(x);

      // No warning for t1
      T t1{4};
  }

  // Only warns on initialization; no warning on global
  int global;

  int g(int i)
  {
      // Warns on x
      int x = 5;

      // No warnings for y or p
      int y{5};
      int p{};

      // Warns on z
      int z = {5};

      // No warning on a
      auto a = y;

      // Warns on b and c
      auto b{y};
      auto c = {y};

      return i * x * y;
  }
