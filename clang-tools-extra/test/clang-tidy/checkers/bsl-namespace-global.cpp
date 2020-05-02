// RUN: %check_clang_tidy %s bsl-namespace-global %t

extern "C" void baz();
extern "C++" void fun();
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: only main, operator new/delete, namespaces, and extern "C" declarations are allowed at global scope [bsl-namespace-global]

namespace N {
static constexpr int foo(int i)
{
  return i * 4;
}

int i;
class C;
}

enum E { e0, e1, e2};
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: only main, operator new/delete, namespaces, and extern "C" declarations are allowed at global scope [bsl-namespace-global]

static_assert(e2 == 2);
// CHECK-MESSAGES: :[[@LINE-1]]:1: warning: only main, operator new/delete, namespaces, and extern "C" declarations are allowed at global scope [bsl-namespace-global]

template<typename T> void f0();
// CHECK-MESSAGES: :[[@LINE-1]]:27: warning: only main, operator new/delete, namespaces, and extern "C" declarations are allowed at global scope [bsl-namespace-global]

class X;
// CHECK-MESSAGES: :[[@LINE-1]]:7: warning: only main, operator new/delete, namespaces, and extern "C" declarations are allowed at global scope [bsl-namespace-global]

int i;
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: only main, operator new/delete, namespaces, and extern "C" declarations are allowed at global scope [bsl-namespace-global]

static int bar()
// CHECK-MESSAGES: :[[@LINE-1]]:12: warning: only main, operator new/delete, namespaces, and extern "C" declarations are allowed at global scope [bsl-namespace-global]
{
  int a1 = N::foo(1);
  return a1;
}

void * operator new(unsigned long size)
{
    return nullptr;
}

void operator delete(void *ptr)
{
    return;
}

int main()
{
    return 0;
}
