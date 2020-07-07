.. title:: clang-tidy - bsl-identifier-typographically-unambiguous

bsl-identifier-typographically-unambiguous
==========================================

Checks that different identifiers are typographically unambiguous

Examples:

.. code-block:: c++

int id1_a_b_c;
int id1_abc; // Warning

int id2_abc;
int id2_ABC; // Warning

int id3_a_bc;
int id3_ab_c; // Warning

int id4_a_bc;
int id4_ab_c; // Warning

int id5_ii;
int id5_11; // Warning

int id6_i0;
int id6_1O; // Warning

int id7_in;
int id7_1h; // Warning

int id8_Z5;
int id8_2S; // Warning

int id9_ZS;
int id9_25; // Warning

void frn0();
void frno(); // Warning

void frn();
void fm(); // Warning
void f___m(); // Warning


