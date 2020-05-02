// RUN: %check_clang_tidy %s bsl-class-virtual-base %t

template<typename T> class X {};
class Y {};

class A : public X<int>, public Y {};

class B : public virtual A {};
// CHECK-MESSAGES: :[[@LINE-1]]:1: warning: class inherits virtual base class [bsl-class-virtual-base]

class C : public virtual A {};
// CHECK-MESSAGES: :[[@LINE-1]]:1: warning: class inherits virtual base class [bsl-class-virtual-base]

class D : public B, public C {};
// CHECK-MESSAGES: :[[@LINE-1]]:1: warning: class inherits virtual base class [bsl-class-virtual-base]
