.. title:: clang-tidy - bsl-op-forbidden-overload

bsl-op-forbidden-overload
=========================

Warns on any call of an overloaded binary logical
operator, comma operator, subscript operator, or addressof
operator.

Examples:

.. code-block:: c++

  struct X {
  private:
      bool b;
      int arr[3];

  public:
      bool operator&&(const X &x)
      {
          return this->b && x.b;
      }

      bool operator||(const X &x)
      {
          return this->b || x.b;
      }

      X& operator,(X &x)
      {
          return x;
      }

      int operator[](int i)
      {
          return (i < 3) ? arr[i] : 0;
      }

      X* operator&()
      {
          return this;
      }
  };

  int foo()
  {
      class X x0;
      class X x1;

      // Emits warning on next 5 lines
      auto a = x0 && x1;
      auto b = x0 || x1;
      X c = (x0, x1);
      int i = c[2];
      X *p = &c;

      return 0;
  }
