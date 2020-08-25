
template <typename T = int>
class basic_errc_type final
{
public:
    constexpr basic_errc_type() noexcept = default;

    explicit constexpr basic_errc_type(T const &errc) noexcept : m_errc{errc}
    {}

    constexpr T const & get() const noexcept
    {
        return m_errc;
    }

    constexpr long message() const noexcept;

private:
    T m_errc;
};

constexpr basic_errc_type<> errc_success{0};
constexpr basic_errc_type<> errc_failure{1};

template<typename T>
constexpr long
basic_errc_type<T>::message() const noexcept
{
    switch (m_errc) {
    case errc_success.get():
        return 1;
    case errc_failure.get():
        return 2;
    default:
        return 3;
    };
}

template<typename T> struct remove_reference { typedef T type; };
template<typename T> struct remove_reference<T&> { typedef T type; };
template<typename T> struct remove_reference<T&&> { typedef T type; };

template<typename T>
constexpr typename remove_reference<T>::type && move(T && arg) noexcept
{
  return static_cast<typename remove_reference<T>::type &&>(arg);
}

struct C {
    float f0;
    float f1;

    C& operator-(const C& rhs)
    {
        f0 -= rhs.f0;
        f1 -= rhs.f1;

        return *this;
    }

    friend C operator+(C lhs, const C& rhs)
    {
        lhs.f0 += rhs.f0;
        lhs.f1 += rhs.f1;
        return lhs;
    }
};

C& operator*(C lhs, const C& rhs)
{
    lhs.f0 *= rhs.f0;
    lhs.f1 *= rhs.f1;

    return lhs;
}

static int f()
{
    return 0;
}

[[maybe_unused]] static int f_unused();

static void g()
{
    auto x = 0;
    auto y = 1;
}

static constexpr int c()
{
    return 2;
}

int z()
{
    int y;

    g();

    f();
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: unused return value [bsl-unused-return-value]

    f_unused();

    int x = f();
    static_cast<void>(f());

    class C c0, c1, c2, c3, c4;

    for (auto i = 0; i < 5; i++) {
        f();
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: unused return value [bsl-unused-return-value]

        x = f();
    }

    do {
        f();
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: unused return value [bsl-unused-return-value]

        y = f();
    } while (0);

    switch (f()) {
    case 1:
        f();
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: unused return value [bsl-unused-return-value]
        x = f();
        static_cast<void>(f());
        break;
    case c():
        break;
    default:
        x = 0;
        break;
    }

    c2 = c0 + c1;
    c0 * c2;
    c1 - c2;
    c4 = c2;
    c3 = move(c4);

    operator*(c0, c2);
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: unused return value [bsl-unused-return-value]

    c2.operator-(c1);
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: unused return value [bsl-unused-return-value]

    return y;
}
