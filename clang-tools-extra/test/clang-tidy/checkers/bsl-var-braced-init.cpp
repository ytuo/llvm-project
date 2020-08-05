// RUN: %check_clang_tidy -std=c++17-or-later %s bsl-var-braced-init %t

namespace std {
template<typename T>
class initializer_list{};
}

template<typename T>
void f(T t)
{
    int x = 4;
    // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: variable 'x' is not initialized via direct list initialization [bsl-var-braced-init]

    T t0(x);
    // CHECK-MESSAGES: :[[@LINE-1]]:7: warning: variable 't0' is not initialized via direct list initialization [bsl-var-braced-init]

    T t1{4};
}

int global;

int g(int i)
{
    int x = 5;
    // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: variable 'x' is not initialized via direct list initialization [bsl-var-braced-init]

    int y{5};
    int p{};

    int z = {5};
    // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: variable 'z' is not initialized via direct list initialization [bsl-var-braced-init]

    auto a = y;
    // CHECK-MESSAGES: :[[@LINE-1]]:10: warning: variable 'a' is not initialized via direct list initialization [bsl-var-braced-init]

    auto b{y};

    auto c = {y};
    // CHECK-MESSAGES: :[[@LINE-1]]:10: warning: variable 'c' is not initialized via direct list initialization [bsl-var-braced-init]

    char buf[8];

    for (auto c : buf) {
       c = 42;
    }

    for (auto &c : buf) {
       c = 42;
    }

    for (char c : buf) {
        c *= c;
    }

    for (auto &&c : buf ) {
        c /= c;
    }

    for (auto i = 0; i < 8; i++) {
    // CHECK-MESSAGES: :[[@LINE-1]]:15: warning: variable 'i' is not initialized via direct list initialization [bsl-var-braced-init]
        buf[i] += buf[i];
    }

    for (auto i{0}; i < 8; i++) {
        buf[i] += buf[i];
    }

    for (int i = 0; i < 8; i++) {
    // CHECK-MESSAGES: :[[@LINE-1]]:14: warning: variable 'i' is not initialized via direct list initialization [bsl-var-braced-init]

        buf[i] += buf[i];
    }

    return i * x * y;
}

int baz(int i = 0)
{
    if (auto j{i}; j > 4)
        return i * 2;
    else if (int k = i * 3; k % 5 == 2)
    // CHECK-MESSAGES: :[[@LINE-1]]:18: warning: variable 'k' is not initialized via direct list initialization [bsl-var-braced-init]
        return 0;

    int pairs[3][2]{{0,0}, {1,1}, {2,2}};
    int sum{};

    for (auto&& [first, second] : pairs) {
        sum += first + second;
    }

    int buf[4];

    for (int n = sum; auto i : buf) {
    // CHECK-MESSAGES: :[[@LINE-1]]:14: warning: variable 'n' is not initialized via direct list initialization [bsl-var-braced-init]
        sum *= n - i * 3;
    }

    return sum;
}

struct C {
   int c;
};

int make_c()
{
    C c;
    // CHECK-MESSAGES: :[[@LINE-1]]:7: warning: variable 'c' is not initialized via direct list initialization [bsl-var-braced-init]
}
