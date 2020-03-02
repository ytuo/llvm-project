#include <stdint.h>

enum e0 { a };
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: enum declaration does not explicitly state underlying type [bsl-enum-explicit]

enum class e1
// CHECK-MESSAGES: :[[@LINE-1]]:12: warning: enum declaration does not explicitly state underlying type [bsl-enum-explicit]
{
  e10,
  e11,
  e12
};

enum e2 : uint64_t { c = 1UL };
enum class e3 : uint8_t { d };
enum class e4 : int { e };

enum class e5 {
// CHECK-MESSAGES: :[[@LINE-1]]:12: warning: enum declaration does not explicitly state underlying type [bsl-enum-explicit]
  f = 42
};

enum struct e6 : uint32_t
{
  g,
  h
};
