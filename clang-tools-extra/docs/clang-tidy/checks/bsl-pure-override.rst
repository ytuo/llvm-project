.. title:: clang-tidy - bsl-pure-override

bsl-pure-override
=================

Warns if a pure virtual function overrides a non-pure function.

Examples:

.. code-block:: c++

  class A
  {
  public:
      virtual ~A() = default;
      virtual void f() = 0;
      virtual void g() noexcept = 0;
  };

  class B : public A {
  public:
      void f() override = 0;
      void g() noexcept override = 0;

      virtual void h()
      {
      }
  };

  class C : public B {
  public:
      void f() override = 0;
      virtual void g() noexcept = 0;

      // Warns here, since h is pure and overrides B::h, which is not pure
      virtual void h() = 0;
  };
