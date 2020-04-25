// RUN: %check_clang_tidy %s bsl-class-base %t

//
// C* classes below are concrete
//

class C0 {
public:
    C0();

    virtual ~C0() = 0;
    virtual void f0() = 0;

    static constexpr int x{3};

    int a;
};

class C1 {
public:
    virtual ~C1() = 0;
    virtual void f1() = 0;

protected:
    int a;
};

class C2 {
public:
    void f2();
    int c2;
};

class C3 {
public:
    int f3();
};

class C4 {
    int f4();
};

class C5 {
public:
    static int x5;
};

class C6 {
    virtual long baz() = 0;

public:
    virtual long zip() = 0;
};

class C7 {
public:
    virtual ~C7() = default;
};

template<typename X> class C8 {
public:
    X foo_c8();
};

template<typename X>
class C9 : public C8<X> {
public:
    virtual ~C9() = default;
    virtual long foo_c9() noexcept = 0;
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
    virtual void fi1() = 0;
    static constexpr int i1{1};
};

class I2 {
public:
    virtual ~I2() = default;
    virtual void fi2() = 0;

    static constexpr int di2{2};
};

class I3 {
public:
    virtual ~I3() = default;
    virtual short fi3() const noexcept = 0;

protected:
    I3(I3 const&) = delete;
    I3(I3 &&) = default;
    I3& operator=(I3 const&) = default;
    I3& operator=(I3 &&) = delete;
};

class I4 : public I0, public I1  {
public:
    virtual ~I4() = default;
    virtual void fi4() = 0;
};

class I5 : public I4 {
public:
    virtual ~I5() = default;
    virtual void fi5() = 0;

    static constexpr int i5{5};
};

class D0;

class D0 : public C0 {};
class D1 : public I0 {};
class D2 : public I0, public I1, public I2, public I3 {};
class D3 : public C1, public I1, public I2, public I3 {};
class D4 : public I0, public C2, public I2, public I3 {};
class D5 : public I0, public I1, public I2, public C4 {};

class D7 : public C1, public C2, public I0 {};
// CHECK-MESSAGES: :[[@LINE-1]]:1: warning: class D7 has 1 interface base classes; at least 2 required [bsl-class-base]
// CHECK-MESSAGES: :[[@LINE-2]]:1: note: a class is an interface if (1) it has a virtual destructor, (2) it has at least one public pure virtual method, (3) its non-special methods are public pure virtual, (4) it has no dependent bases, (5) its base classes (if any) are interfaces, and (6) its data members (if any) are public static constexpr

class D8 : public C1, public C2, public C3, public I0, public I2, public I3 {};
// CHECK-MESSAGES: :[[@LINE-1]]:1: warning: class D8 has 3 interface base classes; at least 5 required [bsl-class-base]
// CHECK-MESSAGES: :[[@LINE-2]]:1: note: a class is an interface if (1) it has a virtual destructor, (2) it has at least one public pure virtual method, (3) its non-special methods are public pure virtual, (4) it has no dependent bases, (5) its base classes (if any) are interfaces, and (6) its data members (if any) are public static constexpr

class D9 : public C7, public I4 {};
class D10 : public C7, public I4, public I2 {};
class D11 : public C7, public I4, public I2, public I3 {};

template<typename X>
class D12 : public I0, public C2, public C9<X> {};
// CHECK-MESSAGES: :[[@LINE-1]]:1: warning: class D12 has 1 interface base classes; at least 2 required [bsl-class-base]
// CHECK-MESSAGES: :[[@LINE-2]]:1: note: a class is an interface if (1) it has a virtual destructor, (2) it has at least one public pure virtual method, (3) its non-special methods are public pure virtual, (4) it has no dependent bases, (5) its base classes (if any) are interfaces, and (6) its data members (if any) are public static constexpr
