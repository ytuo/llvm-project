
constexpr int i = 0;
int j = (i > 0) ? i : 0;

const long k = 42;
const auto n = (k > 43) ? k : j;

void g(int i);

void f()
{
    for (auto k = (j > 0) ? 0 : 1;;) {

    }

    g((j < 2) ? 3 : 5);
    // CHECK-MESSAGES: :[[@LINE-1]]:7: warning: conditional operator used as subexpression [bsl-op-conditional-subexpr]

    long n = j + ((i == 0) ? (i * 2) : 1);
    // CHECK-MESSAGES: :[[@LINE-1]]:19: warning: conditional operator used as subexpression [bsl-op-conditional-subexpr]
}

template<int I = (i < 0) ? 0 : 1>
// CHECK-MESSAGES: :[[@LINE-1]]:18: warning: conditional operator used as subexpression [bsl-op-conditional-subexpr]
int t()
{
    return I;
}
