
int foo(int i, bool b)
{
    int ret;

    switch (i) {
    case 0: {
        ret = 1;
        break;
    }
    case 1:
    case 2:
        if (b) {
        case 3:
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: switch case's parent is neither case label nor switch body [bsl-stmt-switch-case-parent]
            ret = 2;
        }
        if (!b) {
        default:
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: switch case's parent is neither case label nor switch body [bsl-stmt-switch-case-parent]
            ret = i * 2;
            break;
        }
    }

    return ret;
}
