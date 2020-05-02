// RUN: %check_clang_tidy %s bsl-friend-decl %t

class C;

class A {
public:
    A& operator+=(A const& rhs);
    friend A const operator-(A const& lhs, A const& rhs);
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: friend declarations are forbidden [bsl-friend-decl]

    friend class C;
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: friend declarations are forbidden [bsl-friend-decl]
};
