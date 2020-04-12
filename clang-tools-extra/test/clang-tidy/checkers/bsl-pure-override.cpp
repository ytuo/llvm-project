// RUN: %check_clang_tidy %s bsl-pure-override %t

class A
{
public:
    virtual ~A() = default;
    virtual void f() = 0;
    virtual void g() noexcept = 0;
};

class B : public A {
public:
    void f() override = 0;
    void g() noexcept override = 0;

    virtual void h()
    {
    }

private:
    int m_i;
};

class C : public B {
public:
    void f() override = 0;
    virtual void g() noexcept = 0;

    virtual void h() = 0;
    // CHECK-MESSAGES: :[[@LINE-1]]:18: warning: pure function 'h' overrides non-pure function [bsl-pure-override]
    // CHECK-MESSAGES: :16:18: note: found non-pure overridden function here
};

template<typename T>
class D : public B {
public:
    virtual void h() = 0;
    // CHECK-MESSAGES: :[[@LINE-1]]:18: warning: pure function 'h' overrides non-pure function [bsl-pure-override]
    // CHECK-MESSAGES: :16:18: note: found non-pure overridden function here

private:
    T m_t;
};
