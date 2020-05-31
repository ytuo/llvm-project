// RUN: %check_clang_tidy %s bsltest-cast-signedness %t
#include <stdint.h>


// FIXME: Add something that triggers the check here.
void f()
{
	// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: function 'f' is insufficiently awesome [bsltest-cast-signedness]

	// FIXME: Verify the applied fix.
	//   * Make the CHECK patterns specific enough and try to make verified lines
	//     unique to avoid incorrect matches.
	//   * Use {{}} for regular expressions.
	// CHECK-FIXES: {{^}}void awesome_f();{{$}}

	int8_t s8;
	uint8_t u8;
	s8 = static_cast< int8_t >( u8 );	
	// s8 = static_cast< int8_t >( u8 + u8 );		// Warning
	// s8 = static_cast< int8_t >( u8 ) + static_cast< int8_t >( u8 );		// No warning
}

// FIXME: Add something that doesn't trigger the check here.
void awesome_f2();
