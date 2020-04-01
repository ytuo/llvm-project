.. title:: clang-tidy - bsl-stmt-switch-default-break

bsl-stmt-switch-default-break
=============================

Warns whenever a switch statement's default case does not end
with a break or throw.

Examples:

.. code-block:: c++

  static int foo(int x, int y)
  {
      int i;

      switch (x) {
      case 0:
      case 1:
          break;
      // Warns on the line below
      default:
          return y * 2;
      }

      switch (x) {
      case 0:
      case 1:
          break;
      // Warns on the line below
      default:
          if (y)
              return y * 2;
      }

      switch (x) {
      case 0:
      case 1:
          break;
      // Warns on line below
      default:
          for (auto i = x; x < y; x++)
              i = y * 2;
      }

      // No warnings for below switch statements

      switch (x) {
      case 0:
      case 1:
          break;
      default:
          if (y)
              return y * 2;
          break;
      }

      switch (x) {
      case 0:
      case 1:
          break;
      default:
          i = y * 2;
          for (auto i = x; x < y; x++) {
              i = y * 2;
          }
          break;
      }

      switch (x) {
      case 0:
      case 1:
          break;
      default:
          i = y * 2;
          for (auto i = x; x < y; x++) {
              i = y * 2;
          }
          throw;
      }

      switch (x) {
      case 0:
      case 1:
          break;
      default:
          while (x < y) {
              i += x;
              x++;
          }
          break;
      }

      return 0;
  }
