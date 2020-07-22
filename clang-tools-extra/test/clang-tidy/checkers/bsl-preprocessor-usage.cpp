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

#if BAR == 2
#error error
#elif BAR == 4
#else
#endif

// error?
// ident?		#ident #sccs
#line 10		// error?

#undef FOO

// #include <iostream>


void func1();  
void func2();  
    
#pragma startup func1  
#pragma exit func2  #pragma warn -rvl
#pragma warning(disable:4700)
#pragma warn -rvl    

void func1()  
{  
    int x = 1;
}  
    
void func2()  
{  
    int x = 2;
}  
    