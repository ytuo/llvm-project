.. title:: clang-tidy - bsl-stmt-switch-case-parent

bsl-stmt-switch-case-parent
============================

Warns whenever a 'case' or 'default' label of a switch statement does
not have either another case label or the switch body as its parent
statement.

Examples:

.. code-block:: c++

  int foo(int i, bool b)
  {
      int ret;

      switch (i) {
      case 0: {
          ret = 1;
          break;
      }
      case 1:
      case 2:
          if (b) {
          // Warns on the line below
          case 3:
              ret = 2;
          }
          if (!b) {
          // Warns on the line below
          default:
              ret = i * 2;
              break;
          }
      }

      return ret;
  }
