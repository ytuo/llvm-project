#include <stdint.h>

enum e0 { a };

enum class e1
{
  e10,
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: uninitialized enum constant [bsl-enum-init]
  e11,
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: uninitialized enum constant [bsl-enum-init]
  e12 = 2,
  e13
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: uninitialized enum constant [bsl-enum-init]
};

enum e2 : uint64_t { c = 1UL };
enum class e3 : uint8_t { d };
enum class e4 : int { e, z };

enum class e5 {
  f = 42
};

enum struct e6 : uint32_t
{
  g,
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: uninitialized enum constant [bsl-enum-init]
  h = 1,
  i = 4
};

enum struct e7 : uint32_t
{
  i = 42,
  j
};
