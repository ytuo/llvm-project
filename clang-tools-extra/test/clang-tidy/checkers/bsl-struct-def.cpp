// RUN: %check_clang_tidy %s bsl-struct-def %t

struct N final {
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: struct should contain only public data members [bsl-struct-def]
private:
  int i = 3;

public:
  int j;
};

struct T {
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: struct must be defined as final; cannot be base of another struct or class [bsl-struct-def]
public:
  int i;
  int j;
};

struct S final {
public:
  int i;
  int j;
};

struct SL : T {
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: struct must be defined as final; cannot be base of another struct or class [bsl-struct-def]
// CHECK-MESSAGES: :[[@LINE-2]]:8: warning: struct should contain only public data members [bsl-struct-def]
// CHECK-MESSAGES: :[[@LINE-3]]:8: warning: struct should not inherit from another class or struct [bsl-struct-def]
private:
  int i;
  int j;
};

class Aclass : T {
private:
  int i;
  int j;
  Aclass(int i){}; 
  virtual void foo();
};

struct S2 final {
  S2(){};
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: struct should not define special member functions or methods [bsl-struct-def]
};

struct S3 final {
  void foo();
  template <typename T>
  void foo(T t);
};

struct S4 final {
  ~S4();
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: struct should not define special member functions or methods [bsl-struct-def]
};

struct S5 final {
  S5(const S5 &);
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: struct should not define special member functions or methods [bsl-struct-def]
};

struct S6 final {
  S6 &operator=(const S6 &);
  // CHECK-MESSAGES: :[[@LINE-1]]:7: warning: struct should not define special member functions or methods [bsl-struct-def]
};

struct S7 final {
  S7(S7 &&); // move-constructor
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: struct should not define special member functions or methods [bsl-struct-def]
};

struct S8 final {
  S8 &operator=(S8 &&); // move-assignment
  // CHECK-MESSAGES: :[[@LINE-1]]:7: warning: struct should not define special member functions or methods [bsl-struct-def]
};

struct S9 final {
  S9(int i){};  // constuctor with params
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: struct should not define special member functions or methods [bsl-struct-def]
};

struct S10 final {
  virtual ~S10();
  // CHECK-MESSAGES: :[[@LINE-1]]:11: warning: struct should not define special member functions or methods [bsl-struct-def]
};

struct S11 final {
  virtual void foo();
  // CHECK-MESSAGES: :[[@LINE-1]]:16: warning: struct should not have virtual members [bsl-struct-def]
};

// Explicitly defaulted or deleted constructors allowed
struct S12 final {
  S12() = default;
};

struct S13 final {
  S13() = delete;
};
