// RUN: %check_clang_tidy %s bsl-for-loop %t

// A6-5-2
void foo()
{
	int y = 0;

	long double l = 0;
	//

	double d = 0;
	//

	double d2 = 0.0;
	//

	double d3;
	//

	d3 = 0;

	int f = 0.0;
	//

	for (int i = 0; i < 3; ++i) {}

	for (int x = 0; x < 3 && y < 15; x++, y++) {}
	//

	for (float z = 0.0F; z < 1; z += 0.1F) {}
	//
	//

	for (float z = 0.0F; z < 3; z += 1) {}
	//

	float w;
	//

	for (w = 0; w < 3; w += 1) {}

	for (w = 0.0F; w < 3; w += 1) {}
	//

	for (int i = 0.0F; i < 3; i += 1) {}
	//

	for (int i = 0; i < 3; i += 0.1F) {}
	//

	for (int i = 0; i < 3.0F; i++) {}
	//
}


