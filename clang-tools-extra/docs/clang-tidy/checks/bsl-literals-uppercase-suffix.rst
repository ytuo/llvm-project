.. title:: clang-tidy - bsl-literals-uppercase-suffix

bsl-literals-uppercase-suffix
=============================

Checks that each integer literal has an uppercase integer suffix.

Examples:

.. code-block:: c++

  // Warns each of the statements below
  int a = 1u;
  int b = 1l;
  int c = 1ul;
  int d = 1uLL;
  int e = 1LLu;

  // No warnings here:
  int f = 1U;
  int g = 1UL;
  int h = 1LLU;
