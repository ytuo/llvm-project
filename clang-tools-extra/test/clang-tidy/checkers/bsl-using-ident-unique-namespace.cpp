// RUN: %check_clang_tidy %s bsl-using-ident-unique-namespace %t
// #include <cstdint>

using func = void (*)(int, int);	// Compliant

namespace n1
{
	using func = void (*)(int, int);
	void f1()
	{
		using func = void (*)(void); // Non-compliant, reuses func identifier declared
			// in the same namespace
	}

	template <class T>
	using ptr = T*;
	// using ptr = int*;
	using myptr = int*;

	template <class T>
	void f2() {
		using ptr = T*;
	}
}

namespace n2
{
	using func = void (*)(int, int); // Compliant, reuses func identifier but in another namespace
	template <class T>
	using ptr = T*;
}


namespace n3
{
	using func = void (*)(int, int);
	namespace n4
	{
		using func = void (*)(int, int); // Non-compliant; nested namespace
		namespace n5 {
			using func = void (*)(int);	 // Non-compliant
		}
	}
}

// ok

namespace n4
{
	// https://en.cppreference.com/w/cpp/language/type_alias
	template<class T>
	using ptr = T*;

	// using ptr = int*;
	
	using myptr = int*;
}

// namespace n5
// {
// 	// template <typename T> using Y = void <typename T> f();
// 	template <typename T> 
// 	void foo();
// 	template <typename T> using f = foo;
// 	void f1()
// 	{
// 		template <typename T> using Y = void <typename T> f();
// 	}
// }


// // already not allowed by clang?
class Type {};

// template <class T>
// using Type = T;

// struct Type { }; // Non-compliant, Type name reused
// enum class Type : int { }; // Non-compliant, Type name reused
// union Type {};
// typedef int Type;
// // using Type = 3;