struct C {
    float f0;
    float f1;

    C& operator-(const C& rhs)
    {
        f0 -= rhs.f0;
        f1 -= rhs.f1;

        return *this;
    }

    friend C operator+(C lhs, const C& rhs)
    {
        lhs.f0 += rhs.f0;
        lhs.f1 += rhs.f1;
        return lhs;
    }
};

C& operator*(C lhs, const C& rhs)
{
    lhs.f0 *= rhs.f0;
    lhs.f1 *= rhs.f1;

    return lhs;
}

static int f()
{
    return 0;
}

static void g()
{
    auto x = 0;
    auto y = 1;
}

static constexpr int c()
{
    return 2;
}

int z()
{
    int y;

    g();

    f();
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: unused return value [bsl-unused-return-value]

    int x = f();
    static_cast<void>(f());

    class C c0, c1, c2;

    for (auto i = 0; i < 5; i++) {
        f();
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: unused return value [bsl-unused-return-value]

        x = f();
    }

    do {
        f();
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: unused return value [bsl-unused-return-value]

        y = f();
    } while (0);

    switch (f()) {
    case 1:
        f();
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: unused return value [bsl-unused-return-value]
        x = f();
        static_cast<void>(f());
        break;
    case c():
        break;
    default:
        x = 0;
        break;
    }

    c2 = c0 + c1;
    c0 * c2;
    c1 - c2;

    operator*(c0, c2);
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: unused return value [bsl-unused-return-value]

    c2.operator-(c1);
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: unused return value [bsl-unused-return-value]

    return y;
}
