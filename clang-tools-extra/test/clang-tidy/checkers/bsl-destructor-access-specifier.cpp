// RUN: %check_clang_tidy %s bsl-destructor-access-specifier %t

class A { // Non-compliant
public:
  ~A()
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: base class destructor must be public virtual, public override, or protected non-virtual. If public destructor is nonvirtual, then class must be declared final. [bsl-destructor-access-specifier]
  {}
};

class B : public A {};
// CHECK-MESSAGES: :[[@LINE-1]]:7: warning: base class destructor must be public virtual, public override, or protected non-virtual. If public destructor is nonvirtual, then class must be declared final. [bsl-destructor-access-specifier]

class C { // Compliant
public:
  virtual ~C()
  {}
};

class D : public C {};

class E { // Compliant
protected:
  ~E();
};

class F // Non-compliant
{
public:
  ~F() = default;
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: base class destructor must be public virtual, public override, or protected non-virtual. If public destructor is nonvirtual, then class must be declared final. [bsl-destructor-access-specifier]
};

class G final // Compliant
{
public:
  ~G() = default;
};

class H // Compliant
{
public:
  virtual ~H() = default;
};

class I : public F {};
// CHECK-MESSAGES: :[[@LINE-1]]:7: warning: base class destructor must be public virtual, public override, or protected non-virtual. If public destructor is nonvirtual, then class must be declared final. [bsl-destructor-access-specifier]

class J : public H {};

class K : H // compliant
{
public:
  ~K() override = default;
};

class L : H // Non-compliant
{
private:
  ~L() override = default;
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: base class destructor must be public virtual, public override, or protected non-virtual. If public destructor is nonvirtual, then class must be declared final. [bsl-destructor-access-specifier]
};


template <typename T> class X { // Non-compliant
private:
  T t;

public:
  T get_t() { return t; }
  ~X() = default;
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: base class destructor must be public virtual, public override, or protected non-virtual. If public destructor is nonvirtual, then class must be declared final. [bsl-destructor-access-specifier]
};

template <typename T> class Y final {
public:
  ~Y() = default; 
};

template <typename T> class Z {
public:
  virtual ~Z() = default; 
};

auto test = []{ return 3; };
