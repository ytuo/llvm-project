// RUN: %check_clang_tidy %s bsltest-bitwise-type %t
#include <stdint.h>

// FIXME: Add something that triggers the check here.
int main()
{
  uint8_t a1 = 4U;
  uint16_t a2 = 5U;
  uint8_t a8;
  uint16_t a16;


  a8 = a1 >> 1 ;	   // Non-compliant
  a8 = a1 << 1;     // Compliant
  a8 = ~a1;				 // Compliant
  a8 = (static_cast<uint8_t>(~a1)) >> 1 ;   // Compliant
  a16 = (static_cast<uint16_t>(~a1)) >> 1 ; // Compliant
  a8 = (uint8_t)(~a1) >> 1 ;       // Non-compliant
  a16 = ((a1 << 4) & a2 ) >> 6;		// Non-compliant

  a16 = ((static_cast<uint8_t>(a1) << 4) & a2) >> 6;		// Non-compliant
  a16 = ((static_cast<uint16_t>(a1) << 4) & a2) >> 6;		// Non-compliant
  a16 = (static_cast<uint16_t> (a1 << 4) & a2) >> 6;		// Non-compliant
  a16 = (static_cast<uint8_t>(static_cast<uint16_t>(a1) << 4) & a2) >> 6;		// Non-compliant
  a16 = (static_cast<uint16_t>(static_cast<uint16_t>(a1) << 4) & a2) >> 6;		// Compliant

  a8 <<= ~a1;   // Non-compliant
  a8 >>= ~a1;   // Non-compliant

  unsigned long a3 = 4;
  unsigned long a4;

  a4 = ((a3 << 4) & a2 ) >> 6;   // Compliant

  unsigned char a0 = 'H';
  unsigned char a5;
  a5 = ~a0 >> 1;   // Non-compliant
  a5 = a0 << 1;   // Compliant

  return 0;
}
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: function 'f' is insufficiently awesome [bsltest-bitwise-type]

// FIXME: Verify the applied fix.
//   * Make the CHECK patterns specific enough and try to make verified lines
//     unique to avoid incorrect matches.
//   * Use {{}} for regular expressions.
// CHECK-FIXES: {{^}}void awesome_f();{{$}}

// FIXME: Add something that doesn't trigger the check here.
void awesome_f2();
