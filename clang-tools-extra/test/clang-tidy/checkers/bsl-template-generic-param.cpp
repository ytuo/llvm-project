// RUN: %check_clang_tidy %s bsl-template-generic-param %t

class A {
public:
  // Template constructor like copy constructor
  template <typename T> A(T const &rhs) {}
  // CHECK-MESSAGES: [[@LINE-1]]:25: warning: a copy constructor should be declared when there is a template constructor with a single parameter that is a generic parameter. [bsl-template-generic-param]

  // Like copy assignment
  template <typename T> T &operator=(T const &rhs) { return *this; }
  // CHECK-MESSAGES: [[@LINE-1]]:28: warning: a copy assignment operator should be declared when there is a template assignment operator with a parameter that is a generic parameter. [bsl-template-generic-param]
};

class B {
public:
  // Copy constructor
  B(const B &old_obj) {}
  // Copy assignment
  B &operator=(const B &other) {}

  template <typename T> B(T const &rhs) {}

  template <typename T> T &operator=(T const &rhs) { return *this; }
};

// Additional
template <typename T> class C {
public:
  // Template type from class template, not from function template
  template <typename Y> C(T const &rhs) {}

  C &operator=(T const &rhs) { return *this; }
};

class D {
public:
  template <typename T> D(T myvar) {}
  // CHECK-MESSAGES: [[@LINE-1]]:25: warning: a copy constructor should be declared when there is a template constructor with a single parameter that is a generic parameter. [bsl-template-generic-param]
};

template <typename T> class E {
public:
  template <typename Y> E(T myvar2) {}
};

template <typename T> class F {
public:
  template <typename Y> F(Y myvar2) {}
  // CHECK-MESSAGES: [[@LINE-1]]:25: warning: a copy constructor should be declared when there is a template constructor with a single parameter that is a generic parameter. [bsl-template-generic-param]
};

class G {
public:
  // More than one parameter
  template <typename T> G(T const &rhs, int i) {}

  template <typename T> G(T const &rhs, T const &foo) {}

  // Non-generic parameter
  template <typename T> T &operator=(int i) { return *this; }
};
