.. title:: clang-tidy - bsl-for-loop-counter

bsl-for-loop-counter-counter
====================

Checks that for loops contain a single loop-counter that is not of floating point type.

Examples:

.. code-block:: c++

  constexpr float zlimit = 2.5F;
  // Warning:
  for (float z = 0.0F; z != zlimit; z += 0.1F) {}

  // No warnings here:
  constexpr std::int32_t ilimit = 100;
  for (std::int32_t i = 0; i < ilimit; ++i) {}
