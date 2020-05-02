// RUN: %check_clang_tidy %s bsl-decl-forbidden %t

union U0;
// CHECK-MESSAGES: :[[@LINE-1]]:1: warning: unions are forbidden [bsl-decl-forbidden]

union U1 {
// CHECK-MESSAGES: :[[@LINE-1]]:1: warning: unions are forbidden [bsl-decl-forbidden]
    int i;
    long l;

    int f0:1;
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: bitfields are forbidden [bsl-decl-forbidden]
};

struct S {
    int f0:2;
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: bitfields are forbidden [bsl-decl-forbidden]

    int f1:30;
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: bitfields are forbidden [bsl-decl-forbidden]
};
