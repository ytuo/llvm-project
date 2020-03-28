.. title:: clang-tidy - bsl-op-mixed-increment-decrement

bsl-op-mixed-increment-decrement
================================

Warns if the increment or decrement operators are mixed with
other operators. This check does not apply to overloaded increment
or decrement operators.

Examples:

.. code-block:: c++

  int i = 0;
  // No warning
  int p = j++;

  // Warning here
  int j = ++i + 2;

  void f()
  {
      int buf[10];

      // Warns on line below
      p = buf[--j];

      // Warns on line below
      if (++k) {

      }

      do {
        // No warning here...
        i--;
      // ...but does warn here
      } while (i-- > 0);

      // No warning below
      for (int q = 0; q < 10; q++) {

      }
  }
