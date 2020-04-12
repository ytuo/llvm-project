// RUN: %check_clang_tidy %s bsl-class-final-function %t

class A
{
public:
    virtual ~A() = default;
    virtual void f() noexcept = 0;
    virtual void g() noexcept {}
};

class B final : public A {
public:
    void f() noexcept final
    {
    }

    void g() noexcept override
    // CHECK-MESSAGES: :[[@LINE-1]]:10: warning: overridden function not marked 'final' in final class [bsl-class-final-function]
    {
    }

    virtual void h() = 0;
    // CHECK-MESSAGES: :[[@LINE-1]]:18: warning: non-overridden virtual function in final class [bsl-class-final-function]

    virtual void z()
    // CHECK-MESSAGES: :[[@LINE-1]]:18: warning: non-overridden virtual function in final class [bsl-class-final-function]
    {

    }
};

class C : public A {
public:
    void f() noexcept final
    {
    }

    void g() noexcept override
    {
    }

    virtual void h() = 0;

    virtual void z()
    {

    }
};
