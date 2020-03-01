.. title:: clang-tidy - bsl-types-no-wide-char

bsl-types-no-wide-char
======================

Checks that wide-character types are used.

Examples:

.. code-block:: c++

  // Warns each of the statements below
  wchar_t a = 0;
  char16_t b = 1;
  char32_t c = 0;
