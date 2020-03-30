
namespace n {
bool s = false;
}

struct X {
    bool p;

    operator bool()
    {
        return this->p;
    }
};

bool foo()
{
    return true;
}

int main()
{
    X y;
    bool set = true, p, q, r;
    bool a[10];
    int x = 2;

    if (y) {}

    if (x - 2 && set) {}
    // CHECK-MESSAGES: :[[@LINE-1]]:15: warning: operands to '&&' must be postfix or '&&' expressions [bsl-op-logical-postfix]
    // CHECK-FIXES: {{^}}    if ((x - 2) && set) {}{{$}}

    if (x == 0 && set) {}
    // CHECK-MESSAGES: :[[@LINE-1]]:16: warning: operands to '&&' must be postfix or '&&' expressions [bsl-op-logical-postfix]
    // CHECK-FIXES: {{^}}    if ((x == 0) && set) {}{{$}}

    if ((x == 0) && set) {}

    if (p || q || r) {}

    if (p || q && ::n::s) {}
    // CHECK-MESSAGES: :[[@LINE-1]]:11: warning: operands to '||' must be postfix or '||' expressions [bsl-op-logical-postfix]
    // CHECK-FIXES: {{^}}    if (p || (q && ::n::s)) {}{{$}}

    if (a[1] && p && y.p) {}

    if (foo() || q) {}

    if (p && !r) {}
    // CHECK-MESSAGES: :[[@LINE-1]]:11: warning: operands to '&&' must be postfix or '&&' expressions [bsl-op-logical-postfix]
    // CHECK-FIXES: {{^}}    if (p && (!r)) {}{{$}}

    if (y.p && r) {}

    if (q && static_cast<bool>(x)) {}

    return 0;
}
