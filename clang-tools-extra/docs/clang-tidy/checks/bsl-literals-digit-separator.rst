.. title:: clang-tidy - bsl-literals-digit-separator

bsl-literals-digit-separator
============================

Warns if any of the following do not hold for digit separators in
integer literals:

- Hex must have one separator per two digits
- Binary must have one separator per four digits
- Decimal must have one separator per three digits

Literals without a digit separator are ignored.

Examples:

.. code-block:: c++

  // Warns on x0-x15
  int x0 = 0x0'0;
  int x1 = 0Xf'1;
  int x2 = 0xA'e;
  int x3 = 0X00'0;
  int x4 = 0x23'0;
  int x5 = 0xb2'3'0;
  int x6 = 1'0;
  int x7 = 92'1;
  int x8 = 9552'1;
  int x9 = 92'31;
  int x10 = 9'200'31ull;
  int x11 = 39'20031;
  int x12 = 0b0'0UL;
  int x13 = 0B1'010;
  int x14 = 0b1011'0;
  int x15 = 0b1111'0011'0LU;

  // No warnings for x16-x31
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




