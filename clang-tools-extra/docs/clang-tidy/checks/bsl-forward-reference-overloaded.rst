.. title:: clang-tidy - bsl-forward-reference-overloaded

bsl-forward-reference-overloaded
================================

Checks that a function that containing a “forwarding reference” as its argument is not overloaded unless the overload has a different number of parameters

Example:

.. code-block:: c++

  template <typename T> void f1(T &&t) {}

  void f1(int &&t) {} // Non-compliant

  void f1(int x, int &&t) {} // Compliant

  template <typename T> void f1(T &&t, int a, int b) {} // Compliant

  template <typename T> void f2(T &&t) {}

  void f2(int &) = delete; // Compliant by deletion

  template <typename T> void f3(T &&t, int a, int b) {} // Compliant

  template <typename T>
  void f3(T &&t, T &&y, int b) {} // Non-compliant, same number of params
