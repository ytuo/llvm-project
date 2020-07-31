// RUN: %check_clang_tidy %s bsl-assign-op-decl-ref-qualifier %t

class A {
public:
  A() = default;

  A& operator=(const A& other) // Non-compliant
  {
    return *this;
  }
  // CHECK-MESSAGES: :[[@LINE-4]]:6: warning: assignment operators should be declared with the ref-qualifier & [bsl-assign-op-decl-ref-qualifier]  

  A& operator=(A&& other) // Non-compliant
  { 
    return *this;
  }
  // CHECK-MESSAGES: :[[@LINE-4]]:6: warning: assignment operators should be declared with the ref-qualifier & [bsl-assign-op-decl-ref-qualifier]  

  A &operator=(int i) // Non-compliant
  {
    return *this;
  }
  // CHECK-MESSAGES: :[[@LINE-4]]:6: warning: assignment operators should be declared with the ref-qualifier & [bsl-assign-op-decl-ref-qualifier]  

  A &operator+=(int i) // Non-compliant
  {
    return *this;
  }
  // CHECK-MESSAGES: :[[@LINE-4]]:6: warning: assignment operators should be declared with the ref-qualifier & [bsl-assign-op-decl-ref-qualifier]

  A &operator-=(int i) // Non-compliant
  {
    return *this;
  }
  // CHECK-MESSAGES: :[[@LINE-4]]:6: warning: assignment operators should be declared with the ref-qualifier & [bsl-assign-op-decl-ref-qualifier]

  A &operator*=(int i) // Non-compliant
  {
    return *this;
  }
  // CHECK-MESSAGES: :[[@LINE-4]]:6: warning: assignment operators should be declared with the ref-qualifier & [bsl-assign-op-decl-ref-qualifier]

  A &operator/=(int i) // Non-compliant
  {
    return *this;
  }
  // CHECK-MESSAGES: :[[@LINE-4]]:6: warning: assignment operators should be declared with the ref-qualifier & [bsl-assign-op-decl-ref-qualifier]

  A &operator%=(int i) // Non-compliant
  {
    return *this;
  }
  // CHECK-MESSAGES: :[[@LINE-4]]:6: warning: assignment operators should be declared with the ref-qualifier & [bsl-assign-op-decl-ref-qualifier]

  A &operator^=(int i) // Non-compliant
  {
    return *this;
  }
  // CHECK-MESSAGES: :[[@LINE-4]]:6: warning: assignment operators should be declared with the ref-qualifier & [bsl-assign-op-decl-ref-qualifier]

  A &operator&=(int i) // Non-compliant
  {
    return *this;
  }
  // CHECK-MESSAGES: :[[@LINE-4]]:6: warning: assignment operators should be declared with the ref-qualifier & [bsl-assign-op-decl-ref-qualifier]

  A &operator|=(int i) // Non-compliant
  {
    return *this;
  }
  // CHECK-MESSAGES: :[[@LINE-4]]:6: warning: assignment operators should be declared with the ref-qualifier & [bsl-assign-op-decl-ref-qualifier]

  A &operator<<=(int i) // Non-compliant
  {
    return *this;
  }
  // CHECK-MESSAGES: :[[@LINE-4]]:6: warning: assignment operators should be declared with the ref-qualifier & [bsl-assign-op-decl-ref-qualifier]

  A &operator>>=(int i) // Non-compliant
  {
    return *this;
  }
  // CHECK-MESSAGES: :[[@LINE-4]]:6: warning: assignment operators should be declared with the ref-qualifier & [bsl-assign-op-decl-ref-qualifier]
};

class B {
public:
  B() = default;
  B& operator=(const B& other) & // Compliant
  {
    return *this;
  }
  B& operator=(B&& other) & // Compliant
  { 
    return *this;
  }
  B &operator=(int) & // Compliant
  {
    return *this;
  }
  B &operator+=(int) & // Compliant
  {
    return *this;
  }
  B &operator-=(int) & // Compliant
  {
    return *this;
  }
  B &operator*=(int) & // Compliant
  {
    return *this;
  }
  B &operator/=(int) & // Compliant
  {
    return *this;
  }
  B &operator%=(int) & // Compliant
  {
    return *this;
  }
  B &operator^=(int i) & // Compliant
  {
    return *this;
  }
  B &operator&=(int i) & // Compliant
  {
    return *this;
  }
  B &operator|=(int i) & // Compliant
  {
    return *this;
  }
  B &operator<<=(int i) & // Compliant
  {
    return *this;
  }
  B &operator>>=(int i) & // Compliant
  {
    return *this;
  }
};
