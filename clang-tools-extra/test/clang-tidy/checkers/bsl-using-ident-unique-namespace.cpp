// RUN: %check_clang_tidy %s bsl-using-ident-unique-namespace %t
// #include <cstdint>
namespace n1
{
	using func = void (*)(int, int);
	void f1()
	{
		using func = void (*)(void); // Non-compliant, reuses func identifier declared
			// in the same namespace
	}
}

namespace n2
{
	using func = void (*)(int, int); // Compliant, reuses func identifier but
	// in another namespace
}