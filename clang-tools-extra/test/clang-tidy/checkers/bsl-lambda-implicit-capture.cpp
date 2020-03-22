
thread_local double c;

void foo()
{
    int a;
    static int b;

    auto f = [&](){ return a + b; };
    // CHECK-MESSAGES: :[[@LINE-1]]:28: warning: implicit capture of variable with automatic storage duration [bsl-lambda-implicit-capture]

    auto g = [=](){ return b; };
    auto h = [&](){ return c; };
    auto i = [a](){ return a * 2; };
    auto j = [&a](){ return a * 3; };
}

class X {
public:
    int x;

    int bar()
    {
        auto f = [this](){ return x * 3; };
        return f();
    }
};

int baz()
{
    class X x0;
    static class X x1;

    x0.x = 1;
    x1.x = 2;

    return x0.bar() * x1.bar();
}
