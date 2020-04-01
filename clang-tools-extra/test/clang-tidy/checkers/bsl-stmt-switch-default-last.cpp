
int foo(int i, bool b)
{
    int ret;

    switch (i) {
    case 1:
    default:
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: default is not last case in switch [bsl-stmt-switch-default-last]
    case 0: {
        ret = 1;
        break;
    }
    case 2:
        ret = i * 2;
        break;
    }

    return ret;
}

long bar(long l)
{
    long ret;

    switch (l) {
    case 3:
        ret = l - 3;
        break;
    case 5:
        ret = l;
        break;
    default:
        ret = l;
        break;
    }

    return ret;
}

int baz(int i, long j)
{
    switch (i) {
    default:
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: default is not last case in switch [bsl-stmt-switch-default-last]
    break;

    case 1:
    case 42:
        return 42;

    case 45:
        switch (j) {
        case 0:
        case 5:
        case 2:
            return i + 1;
        case 7:
            break;
        default:
            return i % 2;
        }

        break;
    }

    return i * j;
}
