.. title:: clang-tidy - bsl-op-equality-virt-memfn-nullptr

bsl-op-equality-virt-memfn-nullptr
==================================

Emits a warning if a pointer to virtual member function
is checked for equality against an expression that is not 'nullptr'.

Examples:

.. code-block:: c++

  struct X {
      virtual ~X() = default;

      virtual int bar()
      {
          return 1;
      }

      int baz()
      {
          return 2;
      }

      int f1()
      {
          return 5;
      }
  };

  char foo()
  {
      X x0;

      // Warns on line below
      if (&X::bar == &X::baz) {
          return 'e';
      }

      // No warning on line below
      if (&X::bar == (nullptr)) {
          return 'e';
      }

      // No warning here
      if (nullptr != &X::bar) {
          return 'n';
      }

      // Warns on line below
      if (&X::f1 != &X::bar) {
          return 'n';
      }

      return 'b';
  }
