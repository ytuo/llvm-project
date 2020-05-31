// RUN: %check_clang_tidy %s bsltest-for-loop %t
#include <cstdint>

// FIXME: Add something that triggers the check here.
int main()
{
	// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: function 'f' is insufficiently awesome [bsltest-for-loop]

	// FIXME: Verify the applied fix.
	//   * Make the CHECK patterns specific enough and try to make verified lines
	//     unique to avoid incorrect matches.
	//   * Use {{}} for regular expressions.
	// CHECK-FIXES: {{^}}void awesome_f();{{$}}
	int y = 0;

	for (int x = 0; x < 3 && y < 15; x++, y++) {
		;
	}

	for (float z = 0.0F; z < 1; z += 0.1F) {
		;
	}

	for (float z = 0.0F; z < 3; z += 1) {
		;
	}

	return 0;
}


// FIXME: Add something that doesn't trigger the check here.
void awesome_f2() {
	for (int i = 0; i < 3, ++i) {
		;
	}
}
