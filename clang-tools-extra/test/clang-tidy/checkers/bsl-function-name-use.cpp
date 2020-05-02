// RUN: %check_clang_tidy %s bsl-function-name-use %t

extern void f(void);
extern void h(void(*)(void));
extern int p();
extern void q(int);

template<typename T>
void f0(int i)
{
    static T t{};

    t += i * 2;
}

int g()
{
    if (0 == f) {
    // CHECK-MESSAGES: :[[@LINE-1]]:14: warning: function name 'f' must be used in call or addressof expression [bsl-function-name-use]
    // CHECK-FIXES: {{^}}    if (0 == &f) {{{$}}

    }

    void (*x)(void) = f;
    // CHECK-MESSAGES: :[[@LINE-1]]:23: warning: function name 'f' must be used in call or addressof expression [bsl-function-name-use]
    // CHECK-FIXES: {{^}}    void (*x)(void) = &f;{{$}}

    if (0 == &f) {
        f();
        return 0;
    }

    h(&f);

    h(f);
    // CHECK-MESSAGES: :[[@LINE-1]]:7: warning: function name 'f' must be used in call or addressof expression [bsl-function-name-use]
    // CHECK-FIXES: {{^}}    h(&f);{{$}}

    q(p());

    f0<int>(1);

    void (*z)(void) = &f;

    return 0;
}
