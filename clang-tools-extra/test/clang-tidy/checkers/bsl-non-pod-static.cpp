//#include <type_traits>

class non_pod {
private:
    int x;
public:
    int y;
};

//static_assert(!std::is_pod<non_pod>::value);

class A {
public:
    static char id;
    static float const pi;
    static non_pod s;
    // CHECK-MESSAGES: :[[@LINE-1]]:20: warning: non-pod type with static storage duration [bsl-non-pod-static]
private:
    non_pod t;
};

//static_assert(!std::is_pod<A>::value);

class B {
public:
private:
    static A a;
    // CHECK-MESSAGES: :[[@LINE-1]]:14: warning: non-pod type with static storage duration [bsl-non-pod-static]
};


class C {
public:
    constexpr C() = default;
};

namespace {
constexpr int maxint = 0;
constexpr C c{};

static A a0;
// CHECK-MESSAGES: :[[@LINE-1]]:10: warning: non-pod type with static storage duration [bsl-non-pod-static]

A a1{};
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: non-pod type with static storage duration [bsl-non-pod-static]
}

void fn() noexcept
{
    static int x{0};
    static A a{};
    // CHECK-MESSAGES: :[[@LINE-1]]:14: warning: non-pod type with static storage duration [bsl-non-pod-static]
}

class D {
public:
    D() = default;
    D(D const&) = default;
    D(D&&) = default;
    D& operator=(D const&) = default;
    D& operator=(D&&) = default;
    ~D() = default;

private:
    static A *instance;
};
