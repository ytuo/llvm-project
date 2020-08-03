// RUN: %check_clang_tidy %s bsl-function-name-use %t

extern void f(void);
extern void h(void(*)(void));
extern int p();
extern void q(int);

template<typename T>
void f0(int i)
{
    static T t{};

    t += i * 2;
}

int g()
{
    if (0 == f) {
    // CHECK-MESSAGES: :[[@LINE-1]]:14: warning: function name 'f' must be used in call or addressof expression [bsl-function-name-use]
    // CHECK-FIXES: {{^}}    if (0 == &f) {{{$}}

    }

    void (*x)(void) = f;
    // CHECK-MESSAGES: :[[@LINE-1]]:23: warning: function name 'f' must be used in call or addressof expression [bsl-function-name-use]
    // CHECK-FIXES: {{^}}    void (*x)(void) = &f;{{$}}

    if (0 == &f) {
        f();
        return 0;
    }

    h(&f);

    h(f);
    // CHECK-MESSAGES: :[[@LINE-1]]:7: warning: function name 'f' must be used in call or addressof expression [bsl-function-name-use]
    // CHECK-FIXES: {{^}}    h(&f);{{$}}

    q(p());

    f0<int>(1);

    void (*z)(void) = &f;

    return 0;
}

template<typename T>
class safe_integral final
{
    T m_val;
    bool m_error;

public:
    using value_type = T;

    constexpr safe_integral() noexcept = default;

    constexpr bool
    failure() const noexcept
    {
        return m_error;
    }

    constexpr safe_integral<value_type>
    max(safe_integral<value_type> const &other) const noexcept
    {
        if (this->failure() || other.failure()) {
            return zero(true);
        }

        return safe_integral<value_type>{(m_val < other.m_val) ? other.m_val : m_val};
    }

    static constexpr safe_integral<value_type>
    zero(bool const err = false) noexcept
    {
        return safe_integral<value_type>{static_cast<value_type>(0), err};
    }
};
