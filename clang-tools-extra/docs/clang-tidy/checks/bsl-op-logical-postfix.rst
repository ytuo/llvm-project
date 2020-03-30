.. title:: clang-tidy - bsl-op-logical-postfix

bsl-op-logical-postfix
======================

Warns if an operand to '&&' or '||' is either not a postfix
expression or not a '&&' or '||' expression, respectively.

Examples:

.. code-block:: c++

  namespace n {
  bool s = false;
  }

  struct X {
      bool p;
  };

  bool foo()
  {
      return true;
  }

  int main()
  {
      X y;
      bool set = true, p, q, r;
      bool a[10];
      int x = 2;

      // Warns on line below. Suggests parentheses around x - 2.
      if (x - 2 && set) {}

      // Warns on line below. Suggests parentheses around x == 0.
      if (x == 0 && set) {}

      if ((x == 0) && set) {}

      if (p || q || r) {}

      // Warns on line below. Suggests parentheses around q && ::n::s
      if (p || q && ::n::s) {}

      if (a[1] && p && y.p) {}

      if (foo() || q) {}

      // Warns on line below. Suggests parentheses around !r
      if (p && !r) {}

      if (y.p && r) {}

      return 0;
  }
