// RUN: %check_clang_tidy %s bsl-explicit-constructor %t

struct X {
    long x;
};

typedef int typedef_int;
using using_long = long;

template<typename U>
struct A {
    A();
    A(X x);
    A(int, int);
    A(int, int, long);
    A(int *);
    A(int &);

    A(unsigned int);
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: constructor 'A' with single argument of builtin type must be marked explicit [bsl-explicit-constructor]
    // CHECK-FIXES: {{^}}    explicit A(unsigned int);{{$}}

    A(unsigned long);
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: constructor 'A' with single argument of builtin type must be marked explicit [bsl-explicit-constructor]
    // CHECK-FIXES: {{^}}    explicit A(unsigned long);{{$}}

    A(volatile unsigned char);
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: constructor 'A' with single argument of builtin type must be marked explicit [bsl-explicit-constructor]
    // CHECK-FIXES: {{^}}    explicit A(volatile unsigned char);{{$}}

    A(const short);
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: constructor 'A' with single argument of builtin type must be marked explicit [bsl-explicit-constructor]
    // CHECK-FIXES: {{^}}    explicit A(const short);{{$}}

    A(typedef_int);
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: constructor 'A' with single argument of builtin type must be marked explicit [bsl-explicit-constructor]
    // CHECK-FIXES: {{^}}    explicit A(typedef_int);{{$}}

    A(using_long);
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: constructor 'A' with single argument of builtin type must be marked explicit [bsl-explicit-constructor]
    // CHECK-FIXES: {{^}}    explicit A(using_long);{{$}}

    template<typename ...T>
    A(T... args)
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: constructor 'A<int>' with single argument of builtin type must be marked explicit [bsl-explicit-constructor]
    // CHECK-FIXES: {{^}}    explicit A(T... args){{$}}
    {
        m_a = {args...};
    }

    int m_a;
};

void foo()
{
    A<char>(0);
}
