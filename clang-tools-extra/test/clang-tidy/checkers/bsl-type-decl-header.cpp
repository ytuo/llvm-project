// RUN: %check_clang_tidy %s bsl-type-decl-header %t

// FIXME: Add something that triggers the check here.
// class BSLTypeDeclHeader {
// 	int foo;
// };
// // CHECK-MESSAGES: :[[@LINE-1]]:6: warning: function 'f' is insufficiently awesome [bsl-type-decl-header]

// class Foo {
// 	int bar;
// };


// int main() {
//     int i = 10;
 
//     for (int i = 0; i < 10; i++) { }

//     return 0;
// }

int foo() {
	return 3;
};

// template<typename T>
// struct Foo
// {
//     T bar;
//     void doSomething(T param) {/* do stuff using T */}
// };
