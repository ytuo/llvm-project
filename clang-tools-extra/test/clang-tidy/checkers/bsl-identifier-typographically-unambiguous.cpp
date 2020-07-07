// RUN: %check_clang_tidy %s bsl-identifier-typographically-unambiguous %t

int id1_a_b_c;
int id1_abc; // Non-compliant
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: Identifier typographically ambiguous with identifier 'id1_a_b_c' on line 3 [bsl-identifier-typographically-unambiguous]

int id2_abc;
int id2_ABC; // Non-compliant
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: Identifier typographically ambiguous with identifier 'id2_abc' on line 7 [bsl-identifier-typographically-unambiguous]

int id3_a_bc;
int id3_ab_c; // Non-compliant
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: Identifier typographically ambiguous with identifier 'id3_a_bc' on line 11 [bsl-identifier-typographically-unambiguous]

int id4_a_bc;
int id4_ab_c; // Non-compliant
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: Identifier typographically ambiguous with identifier 'id4_a_bc' on line 15 [bsl-identifier-typographically-unambiguous]

int id5_ii;
int id5_11; // Non-compliant
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: Identifier typographically ambiguous with identifier 'id5_ii' on line 19 [bsl-identifier-typographically-unambiguous]

int id6_i0;
int id6_1O; // Non-compliant
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: Identifier typographically ambiguous with identifier 'id6_i0' on line 23 [bsl-identifier-typographically-unambiguous]

int id7_in;
int id7_1h; // Non-compliant
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: Identifier typographically ambiguous with identifier 'id7_in' on line 27 [bsl-identifier-typographically-unambiguous]

int id8_Z5;
int id8_2S; // Non-compliant
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: Identifier typographically ambiguous with identifier 'id8_Z5' on line 31 [bsl-identifier-typographically-unambiguous]

int id9_ZS;
int id9_25; // Non-compliant
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: Identifier typographically ambiguous with identifier 'id9_ZS' on line 35 [bsl-identifier-typographically-unambiguous]

void frn0();
void frno();
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: Identifier typographically ambiguous with identifier 'frn0' on line 40 [bsl-identifier-typographically-unambiguous]

void frn();
void fm();
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: Identifier typographically ambiguous with identifier 'frn' on line 44 [bsl-identifier-typographically-unambiguous] 
void f___m();
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: Identifier typographically ambiguous with identifier 'frn' on line 44 [bsl-identifier-typographically-unambiguous]
