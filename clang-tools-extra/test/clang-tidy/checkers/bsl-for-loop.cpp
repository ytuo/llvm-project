// RUN: %check_clang_tidy %s bsl-for-loop %t
#include <cstdint>

// A6-5-2
void foo()
{
	int y = 0;

	for (int i = 0; i < 3; ++i) {}

	for (int x = 0; x < 3 && y < 15; x++, y++) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:38: warning: For loop must have single loop-counter [bsl-bitwise-type]
	// CHECK-FIXES: {{^}}    for (int x = 0; x < 3 && y < 15; x++, y++) {}{{$}}

	for (float z = 0.0F; z < 1; z += 0.1F) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:7: warning: for loop counter cannot be of floating point type [bsl-bitwise-type]
	// CHECK-FIXES: {{^}}    for (float z = 0.0F; z < 1; z += 0.1F) {}{{$}}

	for (float z = 0.0F; z < 3; z += 1) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:7: warning: for loop counter cannot be of floating point type [bsl-bitwise-type]
	// CHECK-FIXES: {{^}}    for (float z = 0.0F; z < 3; z += 1) {}{{$}}

	float w;
	for (w = 0.0F; w < 3; w += 1) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:7: warning: for loop counter cannot be of floating point type [bsl-bitwise-type]
	// CHECK-FIXES: {{^}}    for (w = 0.0F; w < 3; w += 1) {}{{$}}

	for (int i = 0.0F; i < 3; i += 1) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:7: warning: for loop counter cannot be of floating point type [bsl-bitwise-type]
	// CHECK-FIXES: {{^}}    for (int i = 0.0F; i < 3; i += 1)  {}{{$}}

	for (int i = 0; i < 3; i += 0.1F) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:27: warning: for loop counter cannot be of floating point type (increment by float) [bsl-bitwise-type]
	// CHECK-FIXES: {{^}}    for (int i = 0; i < 3; i += 0.1F) {}{{$}}

	for (int i = 0; i < 3.0F; i++) {}
	// CHECK-MESSAGES: :[[@LINE-1]]:20: warning: for loop counter cannot be of floating point type (comparison to float) [bsl-bitwise-type]
	// CHECK-FIXES: {{^}}    for (int i = 0; i < 3.0F; i++) {}{{$}}
}


