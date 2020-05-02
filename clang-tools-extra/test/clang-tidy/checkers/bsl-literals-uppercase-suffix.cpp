
int a = 1u;
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: integer literal suffix is not uppercase [bsl-literals-uppercase-suffix]

int b = 1U;

int c = 1uL;
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: integer literal suffix is not uppercase [bsl-literals-uppercase-suffix]

int d = 1uLL;
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: integer literal suffix is not uppercase [bsl-literals-uppercase-suffix]

int e = 1UL;
int f = 1ULL;

int g = 1lU;
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: integer literal suffix is not uppercase [bsl-literals-uppercase-suffix]

int h = 1lu;
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: integer literal suffix is not uppercase [bsl-literals-uppercase-suffix]

int i = 1l;
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: integer literal suffix is not uppercase [bsl-literals-uppercase-suffix]

int j = 1ll;
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: integer literal suffix is not uppercase [bsl-literals-uppercase-suffix]
