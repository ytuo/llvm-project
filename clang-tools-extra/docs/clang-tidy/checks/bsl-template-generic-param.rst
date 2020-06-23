.. title:: clang-tidy - bsl-template-generic-param

bsl-template-generic-param
==========================

Checks that a copy constructor is declared when there is a template constructor
with a single parameter that is a generic parameter.
Checks that a copy assignment operator is declared when there is a template 
assignment operator with a parameter that is a generic parameter.

Examples:

.. code-block:: c++

  class A {
  public:
    // Template constructor like copy constructor
    template <typename T> A(T const &rhs) {}	// Non-compliant

    // Like copy assignment
    template <typename T> T &operator=(T const &rhs) { return *this; }	// Non-compliant
  };

  class B {
  public:
    // Copy constructor
    B(const B &old_obj) {}
    // Copy assignment
    B &operator=(const B &other) {}

    template <typename T> B(T const &rhs) {}

    template <typename T> T &operator=(T const &rhs) { return *this; }
  };

