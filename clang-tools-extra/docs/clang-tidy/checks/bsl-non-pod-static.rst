.. title:: clang-tidy - bsl-non-pod-static

bsl-non-pod-static
==================

Ensures that each variable that has a non-POD type does
not have static storage duration unless the variable is
constexpr.

Examples:

.. code-block:: c++

  class non_pod {
  private:
      int x;
  public:
      int y;
  };

  //static_assert(!std::is_pod<non_pod>::value);

  class A {
  public:
      // No warnings for these two
      static char id;
      static float const pi;

      // Warns on the line below
      static non_pod s;
  private:
      non_pod t;
  };

  //static_assert(!std::is_pod<A>::value);

  class B {
  public:
  private:
      static A a; // emits a warning here
  };


  class C {
  public:
      constexpr C() = default;
  };

  namespace {
  constexpr int maxint = 0;
  constexpr C c{};

  // warns the two line below
  static A a0;
  A a1{};
  }

  void fn() noexcept
  {
      static int x{0}; // no warning
      static A a{}; // warning
  }

  class D {
  public:
      D() = default;
      D(D const&) = default;
      D(D&&) = default;
      D& operator=(D const&) = default;
      D& operator=(D&&) = default;
      ~D() = default;

  private:
      static A *instance; // no warning
  };
