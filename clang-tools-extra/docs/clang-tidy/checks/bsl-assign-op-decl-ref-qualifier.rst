.. title:: clang-tidy - bsl-assign-op-decl-ref-qualifier

bsl-assign-op-decl-ref-qualifier
================================

Checks that assignment operators are declared with the ref-qualifier &.

Examples:

.. code-block:: c++

  class A {
  public:
    A() = default;
    A &operator=(int i) // Non-compliant
    {
      return *this;
    }

    A &operator+=(int i) // Non-compliant
    {
      return *this;
    }
    A &operator-=(int i) // Non-compliant
    {
      return *this;
    }
    A &operator*=(int i) // Non-compliant
    {
      return *this;
    }
    A &operator/=(int i) // Non-compliant
    {
      return *this;
    }
    A &operator%=(int i) // Non-compliant
    {
      return *this;
    }
    A &operator^=(int i) // Non-compliant
    {
      return *this;
    }
    A &operator&=(int i) // Non-compliant
    {
      return *this;
    }
    A &operator|=(int i) // Non-compliant
    {
      return *this;
    }
    A &operator<<=(int i) // Non-compliant
    {
      return *this;
    }
    A &operator>>=(int i) // Non-compliant
    {
      return *this;
    }
  };

  class B {
  public:
    B() = default;
    B &operator=(int) & // Compliant
    {
      return *this;
    }
    B &operator+=(int) & // Compliant
    {
      return *this;
    }
    B &operator-=(int) & // Compliant
    {
      return *this;
    }
    B &operator*=(int) & // Compliant
    {
      return *this;
    }
    B &operator/=(int) & // Compliant
    {
      return *this;
    }
    B &operator%=(int) & // Compliant
    {
      return *this;
    }
    B &operator^=(int i) & // Compliant
    {
      return *this;
    }
    B &operator&=(int i) & // Compliant
    {
      return *this;
    }
    B &operator|=(int i) & // Compliant
    {
      return *this;
    }
    B &operator<<=(int i) & // Compliant
    {
      return *this;
    }
    B &operator>>=(int i) & // Compliant
    {
      return *this;
    }
  };

