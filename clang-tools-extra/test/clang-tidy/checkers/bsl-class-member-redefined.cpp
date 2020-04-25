// RUN: %check_clang_tidy %s bsl-class-member-redefined %t

class A {
public:
    virtual ~A() = default;
    virtual void g() noexcept {}
    void f() noexcept {}

protected:
    int x{3};

public:
    int y;
    int z;
};

class B : public A {
public:
    void g() noexcept override {}
    void f() noexcept {}
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: member 'f' hides member with the same name in base class A [bsl-class-member-redefined]
    // CHECK-MESSAGES: :[[@LINE-15]]:5: note: member 'f' of base class A found here

    int x{4};
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: member 'x' hides member with the same name in base class A [bsl-class-member-redefined]
    // CHECK-MESSAGES: :[[@LINE-16]]:5: note: member 'x' of base class A found here

private:
    long y();
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: member 'y' hides member with the same name in base class A [bsl-class-member-redefined]
    // CHECK-MESSAGES: :[[@LINE-18]]:5: note: member 'y' of base class A found here
};

class C : public A {
    unsigned int getc;
};

class D : public C {
public:
    static constexpr int z{5};
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: member 'z' hides member with the same name in base class A [bsl-class-member-redefined]
    // CHECK-MESSAGES: :[[@LINE-28]]:5: note: member 'z' of base class A found here

    // No warnings for members that are private in the base class
    unsigned int getc;
};
