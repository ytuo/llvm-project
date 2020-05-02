.. title:: clang-tidy - bsl-class-base

bsl-class-base
==============

Warns if a class has more than one non-interface base class.
This check considers an interface class to be one that:

  1. has a virtual destructor
  2. has at least one public pure virtual member function
  3. all non-special member functions are public pure virtual
  4. it has no dependent bases
  5. its base classes, if any, are interface classes
  6. its data members, if any, are public static constexpr

Examples:

.. code-block:: c++

  //
  // The 'Cx' classes below are concrete
  //

  class C0 {
  public:
      void f0();
      int c0;
  };

  class C1 {
      int f1();
  };

  template<typename X> class C2 {
  public:
      X foo_c2();
  };

  template<typename X>
  class C3 : public C2<X> {
  public:
      virtual ~C3() = default;
      virtual long foo_c3() noexcept = 0;
  };

  //
  // I* classes below are interfaces
  //

  class I0 {
  public:
      virtual ~I0() = default;
      virtual long foo_i0() noexcept = 0;
  };

  class I1 {
  public:
      virtual ~I1() = default;
      virtual short fi1() const noexcept = 0;

  protected:
      I1(I1 const&) = delete;
      I1(I1 &&) = default;
      I1& operator=(I1 const&) = default;
      I1& operator=(I1 &&) = delete;
  };

  class I2 : public I0, public I1  {
  public:
      virtual ~I2() = default;
      virtual void fi2() = 0;
  };

  // Warns here - 0 interface base classes, at least 1 required
  class D0 : public C0, public C1 {};

  // Warns here - 1 interface base class, at least 2 required
  class D1 : public C0, public C1, public I0 {};

  // Warns here - 1 interface base class, at least 2 required
  template<typename X>
  class D2 : public I0, public C0, public C3<X> {};

  // No warnings below
  class D3 : public C0 {};
  class D4 : public I0 {};
  class D5 : public C0, I0 {};
  class D6 : public C0, I0, I1, I2 {};
