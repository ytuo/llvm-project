
enum foo { a = 0 };
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: enum declaration is not scoped with 'class' keyword [bsl-enum-scoped]

enum struct bar {
// CHECK-MESSAGES: :[[@LINE-1]]:13: warning: enum declaration is not scoped with 'class' keyword [bsl-enum-scoped]
    b
};

enum class baz { c };
