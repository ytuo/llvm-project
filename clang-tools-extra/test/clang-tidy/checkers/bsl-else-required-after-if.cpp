// RUN: %check_clang_tidy %s bsl-else-required-after-if %t

namespace bsl
{
    void
    touch() noexcept
    {}
}

void
tests()
{
    int i;
    bool x, y, z;

    if (x) {
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: 'else' is required after 'if' [bsl-else-required-after-if]
        i = 42;
    }

    if (x) {
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: 'else' is required after 'if' [bsl-else-required-after-if]
        if (y) {
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: 'else' is required after 'if' [bsl-else-required-after-if]
            i = 42;
        }
    }

    if (x) {
        if (y) {
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: 'else' is required after 'if' [bsl-else-required-after-if]
            i = 42;
        }
    }
    else {
        i = 0;
    }

    if (x) {
        return;
    }

    if (x) {
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: 'else' is required after 'if' [bsl-else-required-after-if]
        if (y) {
            return;
        }

        bsl::touch();
    }

    if (x) {
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: 'else' is required after 'if' [bsl-else-required-after-if]
        if (y) {
            bsl::touch();
        }
        else {
            return;
        }
    }

    if (x) {
        if (y) {
            // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: 'else' is required after 'if' or add bsl::touch() after `if` [bsl-else-required-after-if]
            return;
        }
    }
    else {
        bsl::touch();
    }

    if (x) {
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: 'else' is required after 'if' [bsl-else-required-after-if]
        if (y) {
            return;
        }
        else {
        // CHECK-MESSAGES: :[[@LINE-1]]:14: warning: do not use 'else' after 'return/continue/break' [bsl-else-required-after-if]
            return;
        }
    }

    if (x) {
        if (y) {
            return;
        }

        return;
    }

    while (true) {
        if (x) {
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: 'else' is required after 'if' or add bsl::touch() after `if` [bsl-else-required-after-if]
            continue;
        }
    }

    while (true) {
        if (x) {
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: 'else' is required after 'if' [bsl-else-required-after-if]
            bsl::touch();
        }
    }

    while (true) {
        if (x) {
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: 'else' is required after 'if' [bsl-else-required-after-if]
            bsl::touch();
        }

        bsl::touch();
    }

    while (true) {
        if (x) {
            continue;
        }

        bsl::touch();
    }

    while (true) {
        if (x) {
            bsl::touch();
        }
        else {
            bsl::touch();
        }
    }

    while (true) {
        if (x) {
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: 'else' is required after 'if' or add bsl::touch() after `if` [bsl-else-required-after-if]
            break;
        }
    }

    while (true) {
        if (x) {
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: 'else' is required after 'if' [bsl-else-required-after-if]
            bsl::touch();
        }
    }

    while (true) {
        if (x) {
        // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: 'else' is required after 'if' [bsl-else-required-after-if]
            bsl::touch();
        }

        bsl::touch();
    }

    while (true) {
        if (x) {
            break;
        }

        bsl::touch();
    }

    while (true) {
        if (x) {
            bsl::touch();
        }
        else {
            bsl::touch();
        }
    }
}
