.. title:: clang-tidy - bsl-class-member-init

bsl-class-member-init
=====================

Warns in any of the following cases:
  - class has fields that use a mixture of in-class initializers
    and constructor initializers
  - constructor doesn't init each field with member initialization list
    (unless they are initialized in-class)

Examples:

.. code-block:: c++

  class A {
  public:

      // Warning here - mixture of constructor initializers and
      // in-class initializers.
      A() : x{1} {}

      int x;
      int y{1};
  };

  class B {
  public:

      // Warning here, B() doesn't initialize all members via
      // member initialization list, and the members are not
      // initialized in-class.
      B()
      {
        b0 = 1;
        b1 = 1;
      }

      int b0;
      int b1;
  };


  // No warnings below
  class C {
  public:

      C() : x{1}, y{2} {}

      int x;
      int y;
  };

  class D {
  public:

      int x{1};
      int y{2};
  };
