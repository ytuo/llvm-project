.. title:: clang-tidy - bsl-class-member-redefined

bsl-class-member-redefined
==========================

Warns if a derived class defines a data member or method that hides a
member with the same name from a base class.

Examples:

.. code-block:: c++

  class A {
  public:
      virtual ~A() = default;
      virtual void g() noexcept {}
      void f() noexcept {}

  protected:
      int x{3};
      int y;

  private:
      int z;
  };

  class B : public A {
  public:
      void g() noexcept override {}

      // Warns here, f is non-virtual function inherited from A
      void f() noexcept {}

      // Warns here, x is inherited from A
      int x{4};

  private:
      // Warns here, y is inherited from A
      long y();

  public:
      // No warning here, A::z is not inherited by B
      int z;
  };
