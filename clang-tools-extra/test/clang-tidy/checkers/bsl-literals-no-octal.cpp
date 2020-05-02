int a = 00;
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: octal literal [bsl-literals-no-octal]

int b = 012;
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: octal literal [bsl-literals-no-octal]

int c = 0456;
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: octal literal [bsl-literals-no-octal]

int d = 1;
int e = 0x1;
int f = 0X023;
int g = 0b1;
int h = 0B0;
int i = 0B01001;

const char *str0 = "";

auto str1 = L"\012";
// CHECK-MESSAGES: :[[@LINE-1]]:13: warning: octal escape sequence [bsl-literals-no-octal]

auto str2 = L"ABCD" L"EFG";

const char *str3 = "\012";
// CHECK-MESSAGES: :[[@LINE-1]]:20: warning: octal escape sequence [bsl-literals-no-octal]

const char *str4 = "\0";

const char *str5 = "\0123";
// CHECK-MESSAGES: :[[@LINE-1]]:20: warning: octal escape sequence [bsl-literals-no-octal]

const char *str7 = "\000";
// CHECK-MESSAGES: :[[@LINE-1]]:20: warning: octal escape sequence [bsl-literals-no-octal]

const char *str8 = "\00";
// CHECK-MESSAGES: :[[@LINE-1]]:20: warning: octal escape sequence [bsl-literals-no-octal]

const char *str9 = "\07";
// CHECK-MESSAGES: :[[@LINE-1]]:20: warning: octal escape sequence [bsl-literals-no-octal]

const char *str10 = "\1";
// CHECK-MESSAGES: :[[@LINE-1]]:21: warning: octal escape sequence [bsl-literals-no-octal]

char c0 = 'a';
char c1 = '\0';

char c2 = '\1';
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: octal escape sequence [bsl-literals-no-octal]

char c3 = '\111';
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: octal escape sequence [bsl-literals-no-octal]

auto c4 = L'\111';
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: octal escape sequence [bsl-literals-no-octal]

auto c5 = L'\04';
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: octal escape sequence [bsl-literals-no-octal]

auto c6 = '\00';
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: octal escape sequence [bsl-literals-no-octal]

auto c7 = u'\04';
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: octal escape sequence [bsl-literals-no-octal]

auto c8 = U'\031';
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: octal escape sequence [bsl-literals-no-octal]

auto c9 = '\031';
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: octal escape sequence [bsl-literals-no-octal]
