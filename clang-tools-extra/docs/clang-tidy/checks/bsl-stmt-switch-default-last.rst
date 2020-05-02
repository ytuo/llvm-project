.. title:: clang-tidy - bsl-stmt-switch-default-last

bsl-stmt-switch-default-last
============================

Warns is a switch statement's default label is not last.

Examples:

.. code-block:: c++

  int foo(int i, int j)
  {
      int ret;

      switch (i) {
      // Warns on the line below
      default:
      case 0: {
          ret = 1;
          break;
      }
      case 1:
      case 2:
          switch (j) {
          case 2:
          case 3:
              ret = j * 3;
              break;
          // No warning here
          default:
              ret = i * j;
              break;
          }
      case 3:
        ret = 2;
        break;
      }

      return ret;
  }
