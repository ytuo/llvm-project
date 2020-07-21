// RUN: %check_clang_tidy %s bsl-preprocessor-usage %t

#ifndef FOO
// CHECK-NOTES: [[@LINE-3]]:2: note: previous #ifndef was here
void f();
#endif

#ifdef FOO
// CHECK-NOTES: [[@LINE-3]]:2: note: previous #ifndef was here
void f2();
#endif

#define BAR 4

#undef FOO

#include "readability-redundant-preprocessor.h"


void func1();  
void func2();  
    
#pragma startup func1  
#pragma exit func2  
    
void func1()  
{  
    int x = 1;
}  
    
void func2()  
{  
    int x = 2;
}  
    