.. title:: clang-tidy - bsl-namespace-global

bsl-namespace-global
====================

This check warns when it finds something other than the main function,
operator new/delete, a namespace, or an extern "C" declaration in the
global scope.

Examples:

.. code-block:: c++

  // Warns on foo(), x, and class C
  int foo();
  long x;

  class C {
      int c;
  };

  // No warnings here
  void * operator new(size_t s)
  {
    return malloc(s);
  }

  // No warnings here
  void operator delete(void *ptr)
  {
    free(ptr);
  }

  // No warnings here
  int main()
  {
      return 0;
  }

  // No warnings here
  extern "C" void reset(int *i)
  {
      *i = 0;
  }

  // No warnings here
  namespace N {
    int bar();
    long y;

    class D {
        int d;
    };
  }
