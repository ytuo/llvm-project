#include <stdint.h>

template<int> void foo()
// CHECK-MESSAGES: :[[@LINE-1]]:10: warning: replace 'int' with a fixed-width type [bsl-fixed-width-ints]
{
    unsigned int bar;
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: replace 'unsigned int' with a fixed-width type [bsl-fixed-width-ints]

    const int baz = 0;
    // CHECK-MESSAGES: :[[@LINE-1]]:11: warning: replace 'int' with a fixed-width type [bsl-fixed-width-ints]

    int *p = 0;
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: replace 'int' with a fixed-width type [bsl-fixed-width-ints]

    long a;
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: replace 'long' with a fixed-width type [bsl-fixed-width-ints]

    char b;
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: replace 'char' with a fixed-width type [bsl-fixed-width-ints]

    unsigned char goodbye;
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: replace 'unsigned char' with a fixed-width type [bsl-fixed-width-ints]

    uint64_t hello;
}
