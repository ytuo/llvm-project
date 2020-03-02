.. title:: clang-tidy - bsl-enum-scoped

bsl-enum-scoped
===============

Checks that all enums are scoped with the 'class' keyword

Examples:

.. code-block:: c++

  // Warns on the two lines below
  enum e0 { a0 };
  enum struct e1 { a1 };

  // Doesn't warn here
  enum class e2 { a2 };
