// RUN: %check_clang_tidy %s bsl-non-pod-classdef %t

class NonPod {
  int a;
  int b;
  virtual void foo();
};

class Trivial {
// CHECK-MESSAGES: :[[@LINE-1]]:7: warning: non-POD class types should have private member data [bsl-non-pod-classdef]
public:
  int a;

private:
  int b;
};

class StandardL {
// CHECK-MESSAGES: :[[@LINE-1]]:7: warning: non-POD class types should have private member data [bsl-non-pod-classdef]
  int a;
  int b;

public:
  ~StandardL();
};

class Pod {
  int a;
  int b;
};

struct NonPodStruct {
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: non-POD type should be defined as a class [bsl-non-pod-classdef]
public:
  int a;

private:
  int b;
};