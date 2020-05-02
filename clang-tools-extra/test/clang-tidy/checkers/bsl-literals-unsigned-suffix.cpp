
int a = 0x42;
int b = 0X43U;
int c = 0x44L;

int d = 0x44Lu;
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: unsigned hex literal does not end with 'U' [bsl-literals-unsigned-suffix]

int e = 0x44LU;
int f = 0x44LLU;

int g = 0X44UL;
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: unsigned hex literal does not end with 'U' [bsl-literals-unsigned-suffix]

int h = 0;
int i = 0U;
int j = 0u;
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: unsigned octal literal does not end with 'U' [bsl-literals-unsigned-suffix]

int k = 0b1u;
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: unsigned binary literal does not end with 'U' [bsl-literals-unsigned-suffix]

int l = 0b1U;

int m = 1lu;
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: unsigned decimal literal does not end with 'U' [bsl-literals-unsigned-suffix]

int n = 1LU;

unsigned int o = 0xffffffff;
// CHECK-MESSAGES: :[[@LINE-1]]:18: warning: unsigned hex literal does not end with 'U' [bsl-literals-unsigned-suffix]

unsigned long p = 0xffffffffffffffffL;
// CHECK-MESSAGES: :[[@LINE-1]]:19: warning: unsigned hex literal does not end with 'U' [bsl-literals-unsigned-suffix]

unsigned long long q = 0xffffffffffffffffLL;
// CHECK-MESSAGES: :[[@LINE-1]]:24: warning: unsigned hex literal does not end with 'U' [bsl-literals-unsigned-suffix]
