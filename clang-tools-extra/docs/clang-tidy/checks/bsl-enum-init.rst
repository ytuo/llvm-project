.. title:: clang-tidy - bsl-enum-init

bsl-enum-init
=============

The check ensures that either none or all or the first only
of constants in each enum declaration are initialized.

Examples:

.. code-block:: c++

  // Warns on the two declarations below
  enum class e1
  {
    e10,
    e11,
    e12 = 2,
    e13
  };

  enum struct e6 : uint32_t
  {
    g,
    h = 1,
    i = 4
  };

  // No warnings for these:
  enum e0 { a };

  enum e2 : uint64_t { c = 1UL };

  enum class e3 : uint8_t {
    d = 3,
    z
  };

  enum e5 {
    foo = 42,
    bar = 45,
    baz = 46
  };
