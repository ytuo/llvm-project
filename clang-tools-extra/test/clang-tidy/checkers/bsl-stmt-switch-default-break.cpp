
static int foo(int x, int y)
{
    int i;

    switch (x) {
    case 0:
    case 1:
        break;
    default:
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: default case must end with break or throw [bsl-stmt-switch-default-break]
        return y * 2;
    }

    switch (x) {
    case 0:
    case 1:
        break;
    default:
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: default case must end with break or throw [bsl-stmt-switch-default-break]
        if (y)
            return y * 2;
    }

    switch (x) {
    case 0:
    case 1:
        break;
    default:
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: default case must end with break or throw [bsl-stmt-switch-default-break]
        for (auto i = x; x < y; x++)
            i = y * 2;
    }

    switch (x) {
    case 0:
    case 1:
        break;
    default:
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: default case must end with break or throw [bsl-stmt-switch-default-break]
        i = y * 2;
    }

    switch (x) {
    case 0:
    case 1:
        break;
    default:
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: default case must end with break or throw [bsl-stmt-switch-default-break]
        while (x < y) {
            i += x;
            x++;
        }
    }

    switch (x) {
    case 0:
    case 1:
        break;
    default:
        if (y)
            return y * 2;
        break;
    }

    switch (x) {
    case 0:
    case 1:
        break;
    default:
        i = y * 2;
        for (auto i = x; x < y; x++) {
            i = y * 2;
        }
        break;
    }

    switch (x) {
    case 0:
    case 1:
        break;
    default:
        i = y * 2;
        for (auto i = x; x < y; x++) {
            i = y * 2;
        }
        throw;
    }

    switch (x) {
    case 0:
    case 1:
        break;
    default:
        while (x < y) {
            i += x;
            x++;
        }
        break;
    }

    return 0;
}
