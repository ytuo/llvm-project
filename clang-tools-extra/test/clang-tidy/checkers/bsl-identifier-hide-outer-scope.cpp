// RUN: %check_clang_tidy %s bsl-identifier-hide-outer-scope %t

int sum = 0;
namespace
{
	int sum; // Non-compliant, hides sum in outer scope
}
class C1
{
	int sum; // Compliant, does not hide sum in outer scope
};
class C2
{
	int sum; // Compliant, does not hide sum in outer scope
	void f1(int sum); 	// Non-compliant?
	void f2() {
		int sum = 0;	// Non-compliant?
	}
};
namespace n1
{
	int sum; // Compliant, does not hide sum in outer scope
}

int idx;

void f1(int);
void f2()
{
	int max = 5;
	for (int idx = 0; idx < max; ++idx) // Non-compliant, hides idx in outer scope
	{
		for (int idx = 0; idx < max; ++idx) // Non-compliant, hides idx in outer scope
		{
		}
	}
}
void f3()
{
	int i = 0;
	int j = 0;
	auto lambda = [i]() {
		int j = 10; // Compliant - j was not captured, so it does not hide
		// j in outer scope
		return i + j;
	};

	// auto lambda2 = [i]() {
	// 	int i = 10;
	// 	// j in outer scope
	// 	return i + j;
	// };

	// int k = 0;
	// int l = 0;
	// auto lambda2 = [k]() {
	// 	int k = 10;
	// 	// j in outer scope
	// 	return k + l;
	// };
}

void f4(int sum) {} // Non-compliant


