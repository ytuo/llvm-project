// RUN: %check_clang_tidy %s bsltest-bitwise-type %t

// FIXME: Add something that triggers the check here.
int main()
{
  unsigned char a0 = 'H';
  unsigned char a3;

  // Check signed not broken
  a3 = (unsigned char)(~a0 << 1) << 1;   // No warning
}
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: function 'f' is insufficiently awesome [bsltest-bitwise-type]

// FIXME: Verify the applied fix.
//   * Make the CHECK patterns specific enough and try to make verified lines
//     unique to avoid incorrect matches.
//   * Use {{}} for regular expressions.
// CHECK-FIXES: {{^}}void awesome_f();{{$}}

// FIXME: Add something that doesn't trigger the check here.
void awesome_f2();
