
struct X {
    virtual ~X() = default;

    virtual int bar()
    {
        return 1;
    }

    int baz()
    {
        return 2;
    }

    int f1()
    {
        return 5;
    }
};

char foo()
{
    X x0;

    if (&X::bar == &X::baz) {
    // CHECK-MESSAGES: :[[@LINE-1]]:17: warning: comparing virtual member function with expression that is not 'nullptr' [bsl-op-equality-virt-memfn-nullptr]
        return 'e';
    }

    if (&X::bar == (nullptr)) {
        return 'e';
    }

    if (nullptr != &X::bar) {
        return 'n';
    }

    if (&X::f1 != &X::bar) {
    // CHECK-MESSAGES: :[[@LINE-1]]:16: warning: comparing virtual member function with expression that is not 'nullptr' [bsl-op-equality-virt-memfn-nullptr]
        return 'n';
    }

    return 'b';
}
