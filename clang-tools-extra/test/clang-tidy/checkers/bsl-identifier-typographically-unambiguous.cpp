// RUN: %check_clang_tidy %s bsl-identifier-typographically-unambiguous %t

// FIXME: Add something that triggers the check here.
void frn0();
void frno();
void frn();
void fm();
void f___m();

int id1_a_b_c;
int id1_abc; // Non-compliant
int id2_abc; // Non-compliant
int id2_ABC; // Non-compliant
int id3_a_bc;
int id3_ab_c; // Non-compliant
int id4_a_bc;
int id4_ab_c; // Non-compliant
int id5_ii;
int id5_11; // Non-compliant
int id6_i0;
int id6_1O; // Non-compliant
int id7_in;
int id7_1h; // Non-compliant
int id8_Z5;
int id8_2S; // Non-compliant
int id9_ZS;
int id9_25; // Non-compliant