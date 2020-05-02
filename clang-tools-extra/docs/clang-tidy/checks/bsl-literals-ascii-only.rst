.. title:: clang-tidy - bsl-literals-ascii-only

bsl-literals-ascii-only
=============================

Checks that only ASCII-encoded string literals are used.

Examples:

.. code-block:: c++

  // Warns each of the statements below
  auto s0 = L"a";
  auto s1 = U"a";
  auto s2 = u"a";

  // No warnings here:
  auto s3 = "a";
