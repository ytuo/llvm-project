.. title:: clang-tidy - bsl-op-bitwise-operands

bsl-op-bitwise-operands
=======================

Warns if operands to binary bitwise operations have different
underlying type.

Examples:

.. code-block:: c++

  void foo()
  {
    short a0 = 4;
    long a1 = 5;
    int a2 = 6;

    // No warning here
    int x = a2 * a2;

    // Warning on each statement below
    short a3 = a0 ^ a1;
    auto a4 = a0 | (a1 & a1);
    long a5 = a2 & a0;

    a5 |= a0;
    a5 &= a0;
    a5 ^= a0;
  }
