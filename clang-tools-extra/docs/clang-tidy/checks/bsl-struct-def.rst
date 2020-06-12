.. title:: clang-tidy - bsl-struct-def

bsl-struct-def
==============

Checks that a struct only contains public data members, does not provide any
special member functions or methods, and is not a base or inherits from
another struct or class

Examples:

.. code-block:: c++

struct N final {    // Warning
  private:
    int i = 3;
  public:
    int j;
  };

  struct T {    // Warning
  public:
    int i;
    int j;
  };

  struct S final {
  public:
    int i;
    int j;
  };

  struct SL : T {    // Warning
  private:
    int i;
    int j;
  };

  class Aclass : T {
  private:
    int i;
    int j;
  };

  struct S2 final {
    S2(){};    // Warning
  };

  struct S3 final {
    void foo();
  };

  struct S4 final {
    ~S4();    // Warning
  };

  struct S5 final {
    S5(const S5 &);    // Warning
  };

  struct S6 final {
    S6 &operator=(const S6 &);    // Warning
  };

  struct S7 final {
    S7(S7 &&);    // Warning, move-constructor
  };

  struct S8 final {
    S8 &operator=(S8 &&);    // Warning, move-assignment
  };

