.. title:: clang-tidy - bsl-types-fixed-width-ints

bsl-types-fixed-width-ints
=============================

Checks that only fixed-width integer types are used.

Examples:

.. code-block:: c++

  // Warns each of the statements below
  int a = 0;
  long b = 1;
  wchar_t c = 0;
  unsigned d = 0;

  // No warnings here:
  uint64_t e = 42;
