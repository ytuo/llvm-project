// RUN: %check_clang_tidy %s bsl-using-decl-scope %t

namespace N {
    namespace N0 {
        static int foo(int x) { return x * 2; }
    }

    struct X {
        static int x;
    };

    using N0::foo;
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: using declaration in header file is not in class or function [bsl-using-decl-scope]

    namespace N0 {
        static long bar(long y) { return y - 2; }
        static int i1;
    }
}

using N::N0::bar;
// CHECK-MESSAGES: :[[@LINE-1]]:1: warning: using declaration in header file is not in class or function [bsl-using-decl-scope]

class C : public N::X {
    using N::X::x;
    int c;

    int num() { return  c * x; }
};

int f2()
{
    using N::N0::i1;

    return N::foo(2) * i1;
}
