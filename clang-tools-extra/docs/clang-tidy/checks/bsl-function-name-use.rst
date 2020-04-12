.. title:: clang-tidy - bsl-function-name-use

bsl-function-name-use
=====================

Warns whenever a function name is used in an expression
that is neither a call nor an address-of expression.

Examples:

.. code-block:: c++

  extern void f(void);
  extern void h(void(*)(void));
  extern int p();
  extern void q(int);

  int g()
  {
      // Warns on line below for 'f'
      if (0 == f) {

      }

      // Warns on line below for 'f'
      void (*x)(void) = f;

      if (0 == &f) {
          f();
          return 0;
      }

      h(&f);

      // Warns on line below for 'f'
      h(f);

      q(p());

      void (*z)(void) = &f;

      return 0;
  }
