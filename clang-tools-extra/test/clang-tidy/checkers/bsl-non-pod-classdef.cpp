// RUN: %check_clang_tidy %s bsl-non-pod-classdef %t

class NonPod{ // not trivial nor standard-layout
    int a;
    int b;
    virtual void foo();
};

class Trivial { // trivial only
public:
    int a;
private:
    int b;
};

class StandardL { // standard-layout only
    int a;
    int b;
public:
    ~StandardL();
};

class Pod {   // trivial & standard-layout, ie POD
    // default private
    int a;
    int b;
};

struct NonPodStruct { //  should be defined as class
public:
    int a;
private:
    int b;
};
