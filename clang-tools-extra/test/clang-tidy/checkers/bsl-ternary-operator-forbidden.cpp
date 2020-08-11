// RUN: %check_clang_tidy %s bsl-ternary-operator-forbidden %t

constexpr int i = 0;
int j = (i > 0) ? i : 0;
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: the ternary operator is forbidden [bsl-ternary-operator-forbidden]

void g(int i);

void f()
{
    for (auto k = (j > 0) ? 0 : 1;;) {
    // CHECK-MESSAGES: :[[@LINE-1]]:19: warning: the ternary operator is forbidden [bsl-ternary-operator-forbidden]
    }

    g((j < 2) ? 3 : 5);
    // CHECK-MESSAGES: :[[@LINE-1]]:7: warning: the ternary operator is forbidden [bsl-ternary-operator-forbidden]

    long n = j + ((i == 0) ? (i * 2) : 1);
    // CHECK-MESSAGES: :[[@LINE-1]]:19: warning: the ternary operator is forbidden [bsl-ternary-operator-forbidden]
}

template<int I = (i < 0) ? 0 : 1>
// CHECK-MESSAGES: :[[@LINE-1]]:18: warning: the ternary operator is forbidden [bsl-ternary-operator-forbidden]
int t()
{
    return I;
}
