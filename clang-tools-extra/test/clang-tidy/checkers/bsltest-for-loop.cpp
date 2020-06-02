// RUN: %check_clang_tidy %s bsltest-for-loop %t
#include <cstdint>

// A6-5-2
int main()
{
	int y = 0;

	for (int i = 0; i < 3; ++i) {}

	for (int x = 0; x < 3 && y < 15; x++, y++) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: For loop must have single loop-counter [bsltest-bitwise-type]
	// CHECK-FIXES: {{^}}    for (int x = 0; x < 3 && y < 15; x++, y++) {}{{$}}

	for (float z = 0.0F; z < 1; z += 0.1F) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: for loop counter cannot be of floating point type [bsltest-bitwise-type]
	// CHECK-FIXES: {{^}}    for (float z = 0.0F; z < 1; z += 0.1F) {}{{$}}

	for (float z = 0.0F; z < 3; z += 1) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: for loop counter cannot be of floating point type [bsltest-bitwise-type]
	// CHECK-FIXES: {{^}}    for (float z = 0.0F; z < 3; z += 1) {}{{$}}

	// check fail
	for (int i = 0.0F; i < 3; i += 1) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: for loop counter cannot be of floating point type [bsltest-bitwise-type]
	// CHECK-FIXES: {{^}}    for (int i = 0; i < 3; i += 0.1F) {}{{$}}

	// check fail
	for (int i = 0; i < 3; i += 0.1F) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: for loop counter cannot be of floating point type [bsltest-bitwise-type]
	// CHECK-FIXES: {{^}}    for (int i = 0; i < 3; i += 0.1F) {}{{$}}

	// check fail
	for (int i = 0; i < 3.0F; i++) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: for loop counter cannot be of floating point type [bsltest-bitwise-type]
	// CHECK-FIXES: {{^}}    for (int i = 0; i < 3.0F; i++) {}{{$}}

	return 0;
}


