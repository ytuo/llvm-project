// RUN: %check_clang_tidy %s bsl-for-loop-counter %t

// A6-5-2
void foo()
{
	int y = 0;

	long double l = 0;
	// CHECK-MESSAGES: :[[@LINE-1]]:2: warning: float type not allowed (variable declaration) [bsl-for-loop-counter]

	double d = 0;
	// CHECK-MESSAGES: :[[@LINE-1]]:2: warning: float type not allowed (variable declaration) [bsl-for-loop-counter]

	double d2 = 0.0;
	// CHECK-MESSAGES: :[[@LINE-1]]:2: warning: float type not allowed (variable declaration) [bsl-for-loop-counter]

	double d3;
	// CHECK-MESSAGES: :[[@LINE-1]]:2: warning: float type not allowed (variable declaration) [bsl-for-loop-counter]

	d3 = 0;

	int f = 0.0;
	// CHECK-MESSAGES: :[[@LINE-1]]:10: warning: float type not allowed (literal) [bsl-for-loop-counter]

	for (int i = 0; i < 3; ++i) {}

	for (int x = 0; x < 3 && y < 15; x++, y++) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:38: warning: for loop must have single loop-counter [bsl-for-loop-counter]
	
	for (int x = 0, y = 0; x < 3 && y < 15; x++, y++) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:45: warning: for loop must have single loop-counter [bsl-for-loop-counter]

	for (int x = 0, y = 0; x < 3; x++) {}

	for (int x = 0; x < 3 && y < 15; x++) {}

	for (float z = 0.0F; z < 1; z += 0.1F) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:7: warning: float type not allowed (variable declaration) [bsl-for-loop-counter]
	// CHECK-MESSAGES: :[[@LINE-2]]:35: warning: float type not allowed (literal) [bsl-for-loop-counter]

	for (float z = 0.0F; z < 3; z += 1) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:7: warning: float type not allowed (variable declaration) [bsl-for-loop-counter]

	float w;
	// CHECK-MESSAGES: :[[@LINE-1]]:2: warning: float type not allowed (variable declaration) [bsl-for-loop-counter]

	for (w = 0; w < 3; w += 1) {}

	for (w = 0.0F; w < 3; w += 1) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: float type not allowed (literal) [bsl-for-loop-counter]

	for (int i = 0.0F; i < 3; i += 1) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:15: warning: float type not allowed (literal) [bsl-for-loop-counter]

	for (int i = 0; i < 3; i += 0.1F) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:30: warning: float type not allowed (literal) [bsl-for-loop-counter]

	for (int i = 0; i < 3.0F; i++) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:22: warning: float type not allowed (literal) [bsl-for-loop-counter]
}


