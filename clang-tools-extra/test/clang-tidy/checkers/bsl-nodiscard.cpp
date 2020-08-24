// RUN: %check_clang_tidy %s bsl-nodiscard %t

int foo1();
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: function 'foo1' should be marked {{\[\[nodiscard\]\]}} or {{\[\[maybe_unused\]\]}} [bsl-nodiscard]

class bar1
{
public:
    int foo2();
    // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: function 'foo2' should be marked {{\[\[nodiscard\]\]}} or {{\[\[maybe_unused\]\]}} [bsl-nodiscard]
};

[[nodiscard]] int foo3();
[[maybe_unused]] int foo4();
void foo5();

class bar2
{
public:
    [[nodiscard]] int foo6();
    [[maybe_unused]] int foo7();
    void foo8();
};
