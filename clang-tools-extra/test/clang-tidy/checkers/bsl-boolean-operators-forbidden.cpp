// RUN: %check_clang_tidy %s bsl-boolean-operators-forbidden %t

bool
foo(int x, int y)
{
    if (x && y) {
    // CHECK-MESSAGES: :[[@LINE-1]]:11: warning: boolean operators && and || are forbidden [bsl-boolean-operators-forbidden]
        return true;
    }

    if (x || y) {
    // CHECK-MESSAGES: :[[@LINE-1]]:11: warning: boolean operators && and || are forbidden [bsl-boolean-operators-forbidden]
        return true;
    }

    if ((x && y) || (y && x)) {
    // CHECK-MESSAGES: :[[@LINE-1]]:12: warning: boolean operators && and || are forbidden [bsl-boolean-operators-forbidden]
    // CHECK-MESSAGES: :[[@LINE-2]]:18: warning: boolean operators && and || are forbidden [bsl-boolean-operators-forbidden]
    // CHECK-MESSAGES: :[[@LINE-3]]:24: warning: boolean operators && and || are forbidden [bsl-boolean-operators-forbidden]
        return true;
    }

    return false;
}

template<bool A, bool B, bool C = A && B>
// CHECK-MESSAGES: :[[@LINE-1]]:37: warning: boolean operators && and || are forbidden [bsl-boolean-operators-forbidden]
using a_template_test = bool;
