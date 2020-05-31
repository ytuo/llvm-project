
#include <stdint.h>

// testing
#include <iostream>
using namespace std;
// end testing

int main()
{
  unsigned char a0 = 'H';
  unsigned short a1 = 0x4;
  unsigned char a2 = 36;

  unsigned char a3;
  unsigned short a4;

  // Check signed not broken
  a3 = ~a0 >> 1;   // Warning
  a3 = a0 << 1;   // No warning

  // a3 = (unsigned char)(a0) >> 1;   // No warning

  // a4 = a1 >> 1; // Warning
  // a4 = a1 << 1; // No warning
  // a4 = (~a1) >> 1;  // Warning
  // a4 = (~a1) << 1;  // No wsrning

  // a4 = (unsigned short)(a1) >> 1;   // No warning
  // a4 = (unsigned short)(~a1) >> 1;   // No warning

  // a1 >>= 1;   // No warning?
  // a1 <<= 1;   // No warning?


  // a0 = ~a0 << 1;  // No warning? 
  // cout << a0 << "\n";
  // a0 = (unsigned char)a0 << 1;
  // cout << a0 << "\n";

  // a1 = a1 << 1;
  // cout << a1 << "\n";
  // a1 = (unsigned short)a1 << 1;
  // cout << a1 << "\n";

  // a2 = a2 << 1;
  // cout << a2 << "\n";
  // a2 = (unsigned char)a2 << 1;
  // cout << a2 << "\n";



  // other bitwise operators, <<=, ~

  return 0;
}

