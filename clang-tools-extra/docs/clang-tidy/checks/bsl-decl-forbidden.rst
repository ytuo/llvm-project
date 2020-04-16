.. title:: clang-tidy - bsl-decl-forbidden

bsl-decl-forbidden
==================

Warns if unions or bitfields are declared.

Example:

.. code-block:: c++

  // Warns on line below
  union U0;

  // Warns on line below
  union U1 {
      int i;
      long l;

      // Warns on next two lines
      int f0:2;
      int f1:30;
  };
