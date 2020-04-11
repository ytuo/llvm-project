.. title:: clang-tidy - bsl-using-decl-scope

bsl-using-decl-scope
====================

This check warns whenever a using declaration is used outside
of a function or class scope in a header file.

Examples:

.. code-block:: c++

  namespace N {
      namespace N0 {
          static int foo(int x) { return x * 2; }
      }

      struct X {
          static int x;
      };

      // Warning is emitted for line below
      using N0::foo;

      namespace N0 {
          static long bar(long y) { return y - 2; }
          static int i1;
      }
  }

  // Warning is emitted for line below
  using N::N0::bar;

  class C : public N::X {
      // No warning here
      using N::X::x;
      int c;

      int num() { return  c * x; }
  };

  int f2()
  {
      // No warning here
      using N::N0::i1;

      return N::foo(2) * i1;
  }

