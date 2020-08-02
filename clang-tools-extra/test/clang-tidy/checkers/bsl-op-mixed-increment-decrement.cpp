
int i = 0;
int j = ++i + 2;
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: use of '++' is mixed with other operations [bsl-op-mixed-increment-decrement]

int p = j++;

void f()
{
    int buf[10];

    p = buf[--j];
    // CHECK-MESSAGES: :[[@LINE-1]]:13: warning: use of '--' is mixed with other operations [bsl-op-mixed-increment-decrement]

    if (int k = i; ++k) {
    // CHECK-MESSAGES: :[[@LINE-1]]:20: warning: use of '++' is mixed with other operations [bsl-op-mixed-increment-decrement]

    }

    do {
        i--;
    } while (i-- > 0);
    // CHECK-MESSAGES: :[[@LINE-1]]:15: warning: use of '--' is mixed with other operations [bsl-op-mixed-increment-decrement]

    for (int q = 0; q < 10; q++) {

    }

    for (auto &e : buf) {
        e = 42;
    }
}
