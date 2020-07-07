.. title:: clang-tidy - bsl-destructor-access-specifier

bsl-destructor-access-specifier
===============================

Warns if destructor of base class is not public virtual, public override, 
or protected non-virtual, unless public destructor is non-virtual in final class.

Example:

.. code-block:: c++

class A {	// Warning
public:
  ~A(){}
};

class B : public A {};	// Warning

class C {	// No warning
public:
  virtual ~C()
  {}
};

class D : public C {};

class E { 	// No warning
protected:
  ~E();
};

class F 	// Warning
{
public:
  ~F() = default;
};

class G final	// No warning
{
public:
  ~G() = default;
};

class H		// Warning
{
public:
  virtual ~H() = default;
};

class I : public F {};	// Warning

class J : public H {};

class K : H 	// No warning
{
public:
  ~K() override = default;
};

class L : H 	// Warning
{
private:
  ~L() override = default;
};


template <typename T> class X { // Non-compliant
private:
  T t;

public:		// Warning
  T get_t() { return t; }
  ~X() = default;
};

template <typename T> class Y final {	// No warning
public:
  ~Y() = default; 
};

template <typename T> class Z {		// No warning
public:
  virtual ~Z() = default; 
};
