
#include <stdint.h>


int main()
{
  unsigned char a0 = 'H';
  unsigned short a1 = 0x4;
  unsigned char a2 = 36;

  unsigned char a3;
  unsigned short a4;

  // Check signed not broken
  a3 = a0 >> 1;   // Warning
  a3 = a0 << 1;   // No warning

  a3 = (unsigned char (a0)) >> 1;   // No warning

  a4 = a1 >> 1; // Warning
  a4 = a1 << 1; // No warning
  a4 = (~a1) >> 1;  // Warning
  a4 = (~a1) << 1;  // No wsrning

  a4 = (unsigned short (a1)) >> 1;   // No warning
  a4 = (unsigned short (~a1)) >> 1;   // No warning

  a1 >>= 1;   // No warning?
  a1 <<= 1;   // No warning?


  return 0;
}

