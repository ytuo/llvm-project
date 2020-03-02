.. title:: clang-tidy - bsl-enum-explicit

bsl-enum-explicit
=================

Ensures that all enum declarations explicitly state the
underlying type of the enum.

Examples:

.. code-block:: c++

  // Warns each of the declarations below
  enum e0 { a };
  enum class e1
  {
    e10,
    e11,
    e12
  };

  // No warnings here:
  enum e2 : uint64_t { c = 1UL };
  enum class e3 : uint8_t { d };
