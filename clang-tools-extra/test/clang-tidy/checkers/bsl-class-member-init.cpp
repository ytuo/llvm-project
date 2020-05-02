// RUN: %check_clang_tidy %s bsl-class-member-init %t

class A {
    A() : x{1} {}
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: must use either in-class initializers for all fields or constructor initializers for all fields [bsl-class-member-init]

    int x;
    int y{1};
    // CHECK-MESSAGES: :[[@LINE-1]]:10: note: found in-class initializer here
};

class B {
public:
    B() : x{1}, y{2} {}

    int x;
    int y;
};

class C {
public:
    int x{1};
    int y{2};
};

class D {
public:
    D() : d0{1}
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: member initializer list does not initialize each field [bsl-class-member-init]
    {
        d1 = 2;
    }

    int d0;
    int d1;
};

class E {
public:
    E()
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: must use either in-class initializers for all fields or constructor initializers for all fields [bsl-class-member-init]
    {
        e0 = 0;
        e1 = 1;
    }

    int e0;
    int e1;
};

class F {
public:
    F();
    F(int arg0, int arg1);

    int f0;
    int f1;
};

F::F() : f0{0} {}
// CHECK-MESSAGES: :[[@LINE-1]]:1: warning: member initializer list does not initialize each field [bsl-class-member-init]

F::F(int arg0, int arg1)
// CHECK-MESSAGES: :[[@LINE-1]]:1: warning: must use either in-class initializers for all fields or constructor initializers for all fields [bsl-class-member-init]
{
    f0 = arg0;
    f1 = arg1;
}
