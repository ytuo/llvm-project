// RUN: %check_clang_tidy %s bsl-using-ident-unique-namespace %t
// #include <cstdint>

namespace n1
{
	using func = void (*)(int, int);
	void f1()
	{
		using func = void (*)(void); // Non-compliant, reuses func identifier declared in the same namespace
		// CHECK-MESSAGES: [[@LINE-1]]:3: warning: func already used in namespace 'n1' at line 6 [bsl-using-ident-unique-namespace]
	}

	template <class T>
	using ptr = T*;
	// using ptr = int*;
	using myptr = int*;

	template <class T>
	void f2() {
		using ptr = T*;		// Non-compliant
		// CHECK-MESSAGES: [[@LINE-1]]:3: warning: func already used in namespace 'n1' at line 14 [bsl-using-ident-unique-namespace]
	}

	class Foo {
	private:
		void func(){};
		// CHECK-MESSAGES: [[@LINE-1]]:
	};

	struct Bar {
		void func(){};
		// CHECK-MESSAGES: [[@LINE-1]]:
	};
}

namespace n2
{
	using func = void (*)(int, int); // Compliant, reuses func identifier but in another namespace
	template <class T>
	using ptr = T*;
	using myptr = int*;
}


namespace n3
{
	using func = void (*)(int, int);
	namespace n4
	{
		using func = void (*)(int, int); // Non-compliant; nested namespace
		// CHECK-MESSAGES: [[@LINE-1]]:3: warning: func already used in namespace 'n3' at line 47 [bsl-using-ident-unique-namespace]
		namespace n5 {
			using func = void (*)(int);	 // Non-compliant
			// CHECK-MESSAGES: [[@LINE-1]]:4: warning: func already used in namespace 'n3::n4' at line 50 [bsl-using-ident-unique-namespace]
		}
	}
}


namespace n5
{
	template <typename T>
	using myType = T;

	template <typename T>
	void f1()
	{
		using myType = T;		// Non-compliant
		// CHECK-MESSAGES: [[@LINE-1]]:3: warning: myType already used in namespace 'n5' at line 63 [bsl-using-ident-unique-namespace]
	}


	// // template <typename T> using Y = void <typename T> f();
	// // template <typename T> 
	// void foo() {};
	// template <typename T> using f = foo;
	// void f1()
	// {
	// 	template <typename T> using Y = void <typename T> f();
	// }
}

using func2 = void (*)(int, int);
// class and struct tests
namespace n6{
	using func2 = void (*)(int, int);
	// CHECK-MESSAGES: [[@LINE-1]]:2: warning: func2 already used in the global namespace at line 47 [bsl-using-ident-unique-namespace]
	using func = void (*)(int, int);
	class Outer {
		using func = void (*)(int, int);
		// CHECK-MESSAGES: [[@LINE-1]]:3: warning: func already used in namespace 'n6' at line 88 [bsl-using-ident-unique-namespace]

		class Inner{
			using func = void (*)(int, int);
			// CHECK-MESSAGES: [[@LINE-1]]:3: warning: func already used in namespace 'n6' at line 47 [bsl-using-ident-unique-namespace]

		};
	};

	class Outer2 {
		using func3 = void (*)(int, int);
		class Inner2{
			using func3 = void (*)(int, int);
			// CHECK-MESSAGES: [[@LINE-1]]:3: warning: func3 already used in namespace 'n6' at line 47 [bsl-using-ident-unique-namespace]

		};
	};

	struct Outer3 {
		using func3 = void (*)(int, int);
		struct Inner3{
			using func3 = void (*)(int, int);
			// CHECK-MESSAGES: [[@LINE-1]]:3: warning: func3 already used in namespace 'n6' at line 47 [bsl-using-ident-unique-namespace]

		};
	};
}


// // already not allowed by clang
class Type {};

// template <class T>
// using Type = T;

// struct Type { }; // Non-compliant, Type name reused
// enum class Type : int { }; // Non-compliant, Type name reused
// union Type {};
// typedef int Type;
// // using Type = 3;