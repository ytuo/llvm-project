.. title:: clang-tidy - bsl-boolean-operators-forbidden

bsl-boolean-operators-forbidden
===============================

The boolean operators && and || are forbidden. Use if/else if/else instead.

For example, convert the following:

.. code-block:: c++

  if (x && y) {
      // --
  }

  if (x || y) {
      // --
  }

to

.. code-block:: c++

  if (x) {
    if (y) {
    // --
    }
  }

  if (x) {
      // --
  }
  else if (y) {
      // --
  }

  // or

  if (x) {
      // --
  }

  if (y) {
      // --
  }
