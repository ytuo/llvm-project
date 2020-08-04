
#include <stdint.h>

int foo()
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
  // CHECK-MESSAGES: :[[@LINE-1]]:20: warning: operands of bitwise operator have unequal types (b1 has type 'unsigned int', b0 has type 'unsigned short') [bsl-op-bitwise-operands]
  uint32_t b3 = b1 & b0;
  // CHECK-MESSAGES: :[[@LINE-1]]:20: warning: operands of bitwise operator have unequal types (b1 has type 'unsigned int', b0 has type 'unsigned short') [bsl-op-bitwise-operands]
  uint32_t b4 = b1 | b0;
  // CHECK-MESSAGES: :[[@LINE-1]]:20: warning: operands of bitwise operator have unequal types (b1 has type 'unsigned int', b0 has type 'unsigned short') [bsl-op-bitwise-operands]
  uint32_t b5 = b1 >> b0;
  // CHECK-MESSAGES: :[[@LINE-1]]:20: warning: operands of bitwise operator have unequal types (b1 has type 'unsigned int', b0 has type 'unsigned short') [bsl-op-bitwise-operands]

  b2 &= b0;
  // CHECK-MESSAGES: :[[@LINE-1]]:6: warning: operands of bitwise operator have unequal types (b2 has type 'unsigned int', b0 has type 'unsigned short') [bsl-op-bitwise-operands]
  b2 |= b0;
  // CHECK-MESSAGES: :[[@LINE-1]]:6: warning: operands of bitwise operator have unequal types (b2 has type 'unsigned int', b0 has type 'unsigned short') [bsl-op-bitwise-operands]
  b2 ^= b0;
  // CHECK-MESSAGES: :[[@LINE-1]]:6: warning: operands of bitwise operator have unequal types (b2 has type 'unsigned int', b0 has type 'unsigned short') [bsl-op-bitwise-operands]
  b2 <<= b0;
  // CHECK-MESSAGES: :[[@LINE-1]]:6: warning: operands of bitwise operator have unequal types (b2 has type 'unsigned int', b0 has type 'unsigned short') [bsl-op-bitwise-operands]
  b2 >>= b0;
  // CHECK-MESSAGES: :[[@LINE-1]]:6: warning: operands of bitwise operator have unequal types (b2 has type 'unsigned int', b0 has type 'unsigned short') [bsl-op-bitwise-operands]

  const uint32_t c0 = 42;
  uint32_t c1 = 43;

  uint32_t c2 = c1 + c0;
  uint32_t c3 = c0 - c1;
  uint32_t c4 = c1 & c0;
  uint32_t c5 = c0 | c1;
  uint32_t c6 = c1 ^ c0;
  uint32_t c7 = c0 * c1;
  uint32_t c8 = c1 / c0;
  uint32_t c9 = c1 % c0;

  c2 ^= c0;
  c2 *= c0;
  c2 += c0;

  volatile uint64_t d0 = 42;
  uint64_t d1 = 1;

  uint64_t d2 = d1 + d0;
  uint64_t d3 = d0 - d1;
  uint64_t d4 = d1 & d0;
  uint64_t d5 = d0 | d1;
  uint64_t d6 = d1 ^ d0;
  uint64_t d7 = d0 * d1;
  uint64_t d8 = d1 / d0;
  uint64_t d9 = d1 % d0;

  d2 /= d0;
  d2 %= d0;
  d2 -= d0;

  return 0;
}
