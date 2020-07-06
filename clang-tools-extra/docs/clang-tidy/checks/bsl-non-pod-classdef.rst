.. title:: clang-tidy - bsl-non-pod-classdef

bsl-non-pod-classdef
====================

Ensures that member data in non-POD class types is private and non-POD types are defined as class.

Examples:

.. code-block:: c++

  class NonPod {	// No warning
    int a;
    int b;
    virtual void foo();
  };

  class Trivial {	// Warning: private attrs
  public:
    int a;

  private:
    int b;
  };

  class StandardL {	// Warning: private attrs (default)
    int a;
    int b;

  public:
    ~StandardL();
  };

  class Pod {		// No warning
    int a;
    int b;
  };

  struct NonPodStruct {	// Warning: non-pod should be defined as class
  public:
    int a;

  private:
    int b;
  };

