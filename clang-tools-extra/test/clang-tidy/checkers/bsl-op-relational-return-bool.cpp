// RUN: %check_clang_tidy %s bsl-op-relational-return-bool %t

class A {
public:
    long operator<(A const& rhs);
    // CHECK-MESSAGES: :[[@LINE-1]]:10: warning: comparison operator does not return bool [bsl-op-relational-return-bool]

    int operator!=(A const& rhs);
    // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: comparison operator does not return bool [bsl-op-relational-return-bool]

    short operator>=(A const& rhs);
    // CHECK-MESSAGES: :[[@LINE-1]]:11: warning: comparison operator does not return bool [bsl-op-relational-return-bool]

    long operator<=(A const& rhs);
    // CHECK-MESSAGES: :[[@LINE-1]]:10: warning: comparison operator does not return bool [bsl-op-relational-return-bool]

    int x;
};


int operator<(A lhs, A rhs);
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: comparison operator does not return bool [bsl-op-relational-return-bool]

int operator>(A lhs, A rhs)
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: comparison operator does not return bool [bsl-op-relational-return-bool]
{
    return -1;
}

bool operator==(A lhs, A rhs)
{
    return lhs.x == rhs.x;
}
