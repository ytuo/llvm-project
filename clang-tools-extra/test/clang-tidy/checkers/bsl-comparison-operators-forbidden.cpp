// RUN: %check_clang_tidy %s bsl-boolean-operators-forbidden %t

bool
foo(int x, int y)
{
    if (x >= y) {
    // CHECK-MESSAGES: :[[@LINE-1]]:11: warning: comparison operators >= and <= are forbidden [bsl-comparison-operators-forbidden]
        return true;
    }

    if (x <= y) {
    // CHECK-MESSAGES: :[[@LINE-1]]:11: warning: comparison operators >= and <= are forbidden [bsl-comparison-operators-forbidden]
        return true;
    }

    if ((x >= y) || (y <= x)) {
    // CHECK-MESSAGES: :[[@LINE-1]]:12: warning: comparison operators >= and <= are forbidden [bsl-comparison-operators-forbidden]
    // CHECK-MESSAGES: :[[@LINE-2]]:24: warning: comparison operators >= and <= are forbidden [bsl-comparison-operators-forbidden]
        return true;
    }

    return false;
}

template<bool A, bool B, bool C = A >= B>
// CHECK-MESSAGES: :[[@LINE-1]]:37: warning: comparison operators >= and <= are forbidden [bsl-comparison-operators-forbidden]
using a_template_test1 = bool;

template<bool A, bool B, bool C = A <= B>
// CHECK-MESSAGES: :[[@LINE-1]]:37: warning: comparison operators >= and <= are forbidden [bsl-comparison-operators-forbidden]
using a_template_test2 = bool;
