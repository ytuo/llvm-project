.. title:: clang-tidy - bsl-literals-no-octal

bsl-literals-no-octal
=====================

Checks that no non-zero octal integer literals nor octal escape sequences
are used.

Examples:

.. code-block:: c++

  // Warns each of the statements below
  int a = 01;
  int b = 073;
  const char *c = "\012";
  const char *d = '\045';
  const char *e = '\755';

  // No warnings here:
  int f = 0U;
  int g = 0x08UL;
  const char *h = "\0";
