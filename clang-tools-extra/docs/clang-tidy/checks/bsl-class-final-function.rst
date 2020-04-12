.. title:: clang-tidy - bsl-class-final-function

bsl-class-final-function
========================

This check warns if a non-overridden virtual function is declared in
final class or if an overridden function is not marked final in a final class.

Examples:

.. code-block:: c++

  class A
  {
  public:
      virtual ~A() = default;

      virtual void f() noexcept = 0;

      virtual void g() noexcept
      {
      }
  };

  class B final : public A {
  public:
      // f marked final, no warning
      void f() noexcept final
      {
      }

      // g is overridden in final class, but not marked final, emits warning
      void g() noexcept override
      {
      }

      // non-overridden virtual function in class marked final, emits warning
      virtual void h() = 0;

      // non-overridden virtual function in class marked final, emits warning
      virtual void z()
      {

      }
  };
