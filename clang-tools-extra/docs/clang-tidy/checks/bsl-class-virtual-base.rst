.. title:: clang-tidy - bsl-class-virtual-base

bsl-class-virtual-base
======================

Warns if a class has any virtual bases.

Example:

.. code-block:: c++

  template<typename T> class X {};
  class Y {};

  class A : public X<int>, public Y {};

  // Warns on the next three lines
  class B : public virtual A {};
  class C : public virtual A {};
  class D : public B, public C {};
