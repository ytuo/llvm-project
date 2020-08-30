.. title:: clang-tidy - bsl-explicit-constructor

bsl-explicit-constructor
========================

Checks that constructors with a single argument of builtin type are marked explicit
to prevent unwanted implicit conversions.

Examples:

.. code-block:: c++
  struct X {
      long x;
  };

  typedef int typedef_int;
  using using_long = long;

  template<typename U>
  struct A {
      A();
      A(X x);
      A(int, int);
      A(int, int, long);
      A(int *);
      A(int &);

      A(unsigned int); // warning
      A(unsigned long); // warning
      A(volatile unsigned long); // warning
      A(const short); // warning
      A(typedef_int); // warning
      A(using_long); // warning

      template<typename ...T>
      A(T... args) // warning
      {
          m_a = {args...};
      }

      int m_a;
  };

  void foo()
  {
      A<char>(0);
  }
