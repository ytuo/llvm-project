
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

template<typename T, T v>
class integral_constant
{
public:
    using type = integral_constant<T, v>;
    using value_type = T;

    static constexpr value_type value{v};

protected:
    ~integral_constant() noexcept = default;

    constexpr integral_constant(integral_constant const &o) noexcept = default;
    constexpr integral_constant(integral_constant &&o) noexcept = default;
    integral_constant &operator=(integral_constant const &o) &noexcept = default;
    integral_constant &operator=(integral_constant &&o) &noexcept = default;
};

template<bool B>
using bool_constant = integral_constant<bool, B>;

using true_type = bool_constant<true>;

template<typename>
using true_type_for = true_type;

using false_type = bool_constant<false>;

template<typename>
using false_type_for = false_type;


template<typename T>
class is_void final : public false_type
{};

template<>
class is_void<void> final : public true_type
{};

template<>
class is_void<void const> final : public true_type
{};

template<typename From, typename To>
[[nodiscard]] constexpr bool
check_is_nothrow_convertible() noexcept
{
    if constexpr (is_void<From>::value && is_void<To>::value) {
        return true;
    }

    return noexcept(is_void<From>::value) && alignof(From) && sizeof(To) && __is_pod(To);
}
