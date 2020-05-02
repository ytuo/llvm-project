// RUN: %check_clang_tidy -std c++14 %s bsl-literals-digit-separator %t

int x0 = 0x0'0;
// CHECK-MESSAGES: :[[@LINE-1]]:10: warning: separators not two hex digits apart (starting from least-significant digit) [bsl-literals-digit-separator]

int x1 = 0Xf'1;
// CHECK-MESSAGES: :[[@LINE-1]]:10: warning: separators not two hex digits apart (starting from least-significant digit) [bsl-literals-digit-separator]

int x2 = 0xA'e;
// CHECK-MESSAGES: :[[@LINE-1]]:10: warning: separators not two hex digits apart (starting from least-significant digit) [bsl-literals-digit-separator]

int x3 = 0X00'0;
// CHECK-MESSAGES: :[[@LINE-1]]:10: warning: separators not two hex digits apart (starting from least-significant digit) [bsl-literals-digit-separator]

int x4 = 0x23'0;
// CHECK-MESSAGES: :[[@LINE-1]]:10: warning: separators not two hex digits apart (starting from least-significant digit) [bsl-literals-digit-separator]

int x5 = 0xb2'3'0;
// CHECK-MESSAGES: :[[@LINE-1]]:10: warning: separators not two hex digits apart (starting from least-significant digit) [bsl-literals-digit-separator]

int x6 = 1'0;
// CHECK-MESSAGES: :[[@LINE-1]]:10: warning: separators not three decimal digits apart (starting from least-significant digit) [bsl-literals-digit-separator]

int x7 = 92'1;
// CHECK-MESSAGES: :[[@LINE-1]]:10: warning: separators not three decimal digits apart (starting from least-significant digit) [bsl-literals-digit-separator]

int x8 = 9552'1;
// CHECK-MESSAGES: :[[@LINE-1]]:10: warning: separators not three decimal digits apart (starting from least-significant digit) [bsl-literals-digit-separator]

int x9 = 92'31;
// CHECK-MESSAGES: :[[@LINE-1]]:10: warning: separators not three decimal digits apart (starting from least-significant digit) [bsl-literals-digit-separator]

int x10 = 9'200'31ull;
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: separators not three decimal digits apart (starting from least-significant digit) [bsl-literals-digit-separator]

int x11 = 39'20031;
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: separators not three decimal digits apart (starting from least-significant digit) [bsl-literals-digit-separator]

int x12 = 0b0'0UL;
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: separators not four binary digits apart (starting from least-significant digit) [bsl-literals-digit-separator]

int x13 = 0B1'010;
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: separators not four binary digits apart (starting from least-significant digit) [bsl-literals-digit-separator]

int x14 = 0b1011'0;
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: separators not four binary digits apart (starting from least-significant digit) [bsl-literals-digit-separator]

int x15 = 0b1111'0011'0LU;
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: separators not four binary digits apart (starting from least-significant digit) [bsl-literals-digit-separator]

auto x16 = 0;
auto x17 = 0x3;
auto x18 = 0XFFL;
auto x19 = 0xE8'FF;
auto x21 = 234L;
auto x22 = 4096;
auto x23 = 4'096ll;
auto x24 = 10'000'000'000u;
auto x25 = 10'000'000'000ULL;
auto x26 = 0B110101Ul;
auto x27 = 0b11'0101Ul;
auto x28 = 0b1000'0101LLU;
auto x29 = 0B1000;
auto x30 = 0x309562;
auto x31 = 0x30'95'62;
