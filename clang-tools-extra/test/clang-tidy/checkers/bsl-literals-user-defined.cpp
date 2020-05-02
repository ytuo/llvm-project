// RUN: %check_clang_tidy %s bsl-literals-user-defined %t

constexpr unsigned long long operator"" _ft(unsigned long long feet)
{
    return feet;
}

constexpr unsigned long long operator"" _m(unsigned long long meters)
{
    return meters;
}

void f()
{
    unsigned long long feet_per_yard = 3_ft;
// CHECK-MESSAGES: :[[@LINE-1]]:40: warning: user-defined literals are forbidden [bsl-literals-user-defined]
    unsigned long long meters = 300_m;
// CHECK-MESSAGES: :[[@LINE-1]]:33: warning: user-defined literals are forbidden [bsl-literals-user-defined]
}
