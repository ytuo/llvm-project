// RUN: %check_clang_tidy %s bsl-auto-type-usage %t


// https://isocpp.org/wiki/faq/cpp14-language


// #include <cstdint>
// #include <vector>
// #include <initializer_list>


// class A
// {
// };

// void f1() noexcept
// {
// 	auto x1 = 5; // Non-compliant - initializer is of fundamental type
// 	auto x2 = 0.3F; // Non-compliant - initializer is of fundamental type
// 	auto x3 = {8}; // Non-compliant - initializer is of fundamental type

// 	std::vector<std::int32_t> v;
// 	auto x4 = v.size(); // Compliant with case (1) - x4 is of size_t type that is returned from v.size() method
// 	auto a = A{}; // Compliant with case (2)

// 	auto lambda1 = []() -> std::uint16_t {
// 		return 5U;
// 	}; // Compliant with case (2) - lambda1 is of non-fundamental lambda expression type
// 	auto x5 = lambda1(); // Compliant with case (1) - x5 is of std::uint16_t type
	
// 	auto x6 = lambda1() - 1; // non-compliant??
// 	auto x7 = std::initializer_list<int>{3};	// non-compliant

// }

// void f2() noexcept
// {
// 	auto lambda1 = [](auto x, auto y) -> decltype(x + y) {
// 		return (x + y);
// 	}; // Compliant with cases (2) and (3)
// 	auto y1 = lambda1(5.0, 10); // Compliant with case (1)
// }

template <typename T>
class B
{
	public:
	T fn(T t);
};

template <typename T>
auto B<T>::fn(T t) -> T // Compliant with case (4)
{
	return t;
}

template <typename T>
class C
{
	auto fn(int x, int y) -> int;  // function return type = auto --> must have template decl?
	public:
	T fn(T t);
};

template <typename U>
auto C<U>::fn(U u) -> U // Compliant? template
{
	return u;
}

template <typename T, typename U>
auto f3(T t, U u) noexcept -> decltype(t + u) // Compliant with case (4)
{
	return (t + u);
}

auto f4();		// Non-compliant; no trailing return

auto f5() {		// Non-compliant; no trailing return
	return 3;
}

auto f6() -> auto {	// Not allowed; no non-auto trailing return
	return 3;
}

auto f7(int x, int y) -> int	// Non-compliant? no template
{
	return x + y;
}

auto f8(int x, int y) 	// Non-compliant; no trailing return
{
	return x + y;
}

template <typename T>
auto f9(T x, T y) -> T; // Compliant? function return type = auto --> must have template decl?


// // // void f4(auto x) 	// not allowed? supported in c++ 20?
// // // {
// // // }