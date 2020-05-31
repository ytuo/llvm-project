
#include <stdint.h>

int main()
{
  short a0 = 4;
  long a1 = 5;
  int a2 = 6;

  short a3 = a0 ^ a1;
  // CHECK-MESSAGES: :[[@LINE-1]]:17: warning: operands of bitwise operator have unequal types (a0 has type 'short', a1 has type 'long') [bsl-op-bitwise-operands]

  auto a4 = a0 | (a1 & a1);
  // CHECK-MESSAGES: :[[@LINE-1]]:16: warning: operands of bitwise operator have unequal types (a0 has type 'short', (a1 & a1) has type 'long') [bsl-op-bitwise-operands]

  long a5 = a2 & a0;
  // CHECK-MESSAGES: :[[@LINE-1]]:16: warning: operands of bitwise operator have unequal types (a2 has type 'int', a0 has type 'short') [bsl-op-bitwise-operands]

  a5 |= a0;
  // CHECK-MESSAGES: :[[@LINE-1]]:6: warning: operands of bitwise operator have unequal types (a5 has type 'long', a0 has type 'short') [bsl-op-bitwise-operands]
  a5 &= a0;
  // CHECK-MESSAGES: :[[@LINE-1]]:6: warning: operands of bitwise operator have unequal types (a5 has type 'long', a0 has type 'short') [bsl-op-bitwise-operands]
  a5 ^= a0;
  // CHECK-MESSAGES: :[[@LINE-1]]:6: warning: operands of bitwise operator have unequal types (a5 has type 'long', a0 has type 'short') [bsl-op-bitwise-operands]
  a5 <<= a0;
  // CHECK-MESSAGES: :[[@LINE-1]]:6: warning: operands of bitwise operator have unequal types (a5 has type 'long', a0 has type 'short') [bsl-op-bitwise-operands]
  a5 >>= a0;
  // CHECK-MESSAGES: :[[@LINE-1]]:6: warning: operands of bitwise operator have unequal types (a5 has type 'long', a0 has type 'short') [bsl-op-bitwise-operands]

  uint16_t b0 = 1;
  uint32_t b1 = 2;

  uint32_t b2 = b1 << b0;
  // CHECK-MESSAGES: :[[@LINE-1]]:20: warning: operands of bitwise operator have unequal types (b1 has type 'uint32_t', b0 has type 'uint16_t') [bsl-op-bitwise-operands]
  uint32_t b3 = b1 & b0;
  // CHECK-MESSAGES: :[[@LINE-1]]:20: warning: operands of bitwise operator have unequal types (b1 has type 'uint32_t', b0 has type 'uint16_t') [bsl-op-bitwise-operands]
  uint32_t b4 = b1 | b0;
  // CHECK-MESSAGES: :[[@LINE-1]]:20: warning: operands of bitwise operator have unequal types (b1 has type 'uint32_t', b0 has type 'uint16_t') [bsl-op-bitwise-operands]
  uint32_t b5 = b1 >> b0;
  // CHECK-MESSAGES: :[[@LINE-1]]:20: warning: operands of bitwise operator have unequal types (b1 has type 'uint32_t', b0 has type 'uint16_t') [bsl-op-bitwise-operands]

  b2 &= b0;
  // CHECK-MESSAGES: :[[@LINE-1]]:6: warning: operands of bitwise operator have unequal types (b2 has type 'uint32_t', b0 has type 'uint16_t') [bsl-op-bitwise-operands]
  b2 |= b0;
  // CHECK-MESSAGES: :[[@LINE-1]]:6: warning: operands of bitwise operator have unequal types (b2 has type 'uint32_t', b0 has type 'uint16_t') [bsl-op-bitwise-operands]
  b2 ^= b0;
  // CHECK-MESSAGES: :[[@LINE-1]]:6: warning: operands of bitwise operator have unequal types (b2 has type 'uint32_t', b0 has type 'uint16_t') [bsl-op-bitwise-operands]
  b2 <<= b0;
  // CHECK-MESSAGES: :[[@LINE-1]]:6: warning: operands of bitwise operator have unequal types (b2 has type 'uint32_t', b0 has type 'uint16_t') [bsl-op-bitwise-operands]
  b2 >>= b0;
  // CHECK-MESSAGES: :[[@LINE-1]]:6: warning: operands of bitwise operator have unequal types (b2 has type 'uint32_t', b0 has type 'uint16_t') [bsl-op-bitwise-operands]

  return 0;
}
