.. title:: clang-tidy - bsl-literals-user-defined

bsl-literals-user-defined
=========================

Warns on usage of user-defined literals.

Examples:

.. code-block:: c++

  constexpr unsigned long long operator"" _ft(unsigned long long feet)
  {
      return feet;
  }

  constexpr unsigned long long operator"" _m(unsigned long long meters)
  {
      return meters;
  }

  void f()
  {
      // Warns on the two lines below
      unsigned long long feet_per_yard = 3_ft;
      unsigned long long meters = 300_m;
  }
