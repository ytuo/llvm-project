// RUN: %check_clang_tidy %s bsl-non-pod-classdef %t

class NonPod {
  int a;
  int b;
  virtual void foo();
};

class Trivial {
public:
  int a;
  // CHECK-MESSAGES: :[[@LINE-1]]:7: warning: non-POD class types should have private member data [bsl-non-pod-classdef]
  static constexpr int x = 10;
  // CHECK-MESSAGES: :[[@LINE-1]]:24: warning: non-POD class types should have private member data [bsl-non-pod-classdef]

private:
  int b;
};

class StandardL {
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

class test final {
  bool var{};

private:
  static constexpr int x = 10;

public:
  static void func(int i, const int x) {}
};
