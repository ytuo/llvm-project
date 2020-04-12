// RUN: %check_clang_tidy %s bsl-var-braced-init %t

namespace std {
template<typename T>
class initializer_list{};
}

template<typename T>
void f(T t)
{
    int x = 4;
    // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: variable is not initialized via direct list initialization [bsl-var-braced-init]

    T t0(x);
    // CHECK-MESSAGES: :[[@LINE-1]]:7: warning: variable is not initialized via direct list initialization [bsl-var-braced-init]

    T t1{4};
}

int global;

int g(int i)
{
    int x = 5;
    // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: variable is not initialized via direct list initialization [bsl-var-braced-init]

    int y{5};
    int p{};

    int z = {5};
    // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: variable is not initialized via direct list initialization [bsl-var-braced-init]

    auto a = y;
    auto b{y};
    // CHECK-MESSAGES: :[[@LINE-1]]:10: warning: variable declared 'auto' is initialized via list initialization [bsl-var-braced-init]
    auto c = {y};
    // CHECK-MESSAGES: :[[@LINE-1]]:10: warning: variable declared 'auto' is initialized via list initialization [bsl-var-braced-init]

    return i * x * y;
}
