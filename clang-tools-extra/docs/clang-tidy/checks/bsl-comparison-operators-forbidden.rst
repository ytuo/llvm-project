.. title:: clang-tidy - bsl-comparison-operators-forbidden

bsl-comparison-operators-forbidden
==================================

The comparison operators >= and <= are forbidden as they have an implicit ||.
Use <, >, or if/else if/else instead.

For example, convert the following:

.. code-block:: c++

  if (x >= y) {
      // do #1
  }
  else {
      // do #2
  }

to

.. code-block:: c++

  if (x < y) {
      // do #2
  }
  else {
      // do #1
  }

  // or

  if (x > y) {
      // do #1
  }
  else if (x == y) {
      // do #1
  }
  else {
      // do #1
  }

