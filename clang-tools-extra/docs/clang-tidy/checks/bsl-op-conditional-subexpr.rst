.. title:: clang-tidy - bsl-op-conditional-subexpr

bsl-op-conditional-subexpr
==========================

Warns whenever a conditional operator is used as a subexpression.

Examples:

.. code-block:: c++

  constexpr int i = 0;

  // No warning here
  int j = (i > 0) ? 0 : 1;

  void g(int i);

  void f()
  {
      // No warning here
      for (auto k = (j > 0) ? 0 : 1;;) {

      }

      // Warnings on two lines below
      g((j < 2) ? 3 : 5);
      long n = j + ((i == 0) ? (i * 2) : 1);
  }

  // Warning on line below
  template<int I = (i < 0) ? 0 : 1>
  int t()
  {
      return I;
  }
