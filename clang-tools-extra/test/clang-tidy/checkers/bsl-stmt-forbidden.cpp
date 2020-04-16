// RUN: %check_clang_tidy %s bsl-stmt-forbidden %t

int g(int x, int y)
{
    if (x) {
        goto mult2;
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: goto statement is forbidden [bsl-stmt-forbidden]
    } else if (x < 5) {
        goto mult3;
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: goto statement is forbidden [bsl-stmt-forbidden]
    } else {
        do {
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: do statement is forbidden [bsl-stmt-forbidden]
            x--;
        } while (x);
    }

mult2:
    y *= 2;
    return y;

mult3:
    y *= 3;
    return y;
}
