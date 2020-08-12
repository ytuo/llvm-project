// RUN: %check_clang_tidy %s bsl-dependent-base-name %t

#include <cstdint> 

// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: function 'f' is insufficiently awesome [bsl-dependent-base-name]
typedef int32_t TYPE;
void g ( );

template <typename T>
class B;

int var;

template <typename T>
class A : public B<T>
{
	void f1 ( )
	{
		TYPE t = 0;
		g ( );
		var = 0; 		// Non-compliant?? use ::var = 0?
	}
	// Non-compliant Example 1
	// Non-compliant Example 2
	void f2 ( )
	{
		::TYPE t1 = 0;
		::g ( );
		// Compliant - explicit use global TYPE
		// Compliant - explicit use global func
		typename B<T>::TYPE t2 = 0; // Compliant - explicit use base TYPE
		this->g ( );
		// Compliant - explicit use base "g"
	}
};

template <typename T>
class B
{
public:
	typedef T TYPE;
	void g ( );
};

template class A<int32_t>;


class C {};

template <typename T>
class D : public C
{
	void f1 ( )
	{
		TYPE t = 0;
		g ( );
	}
	void f2 ( )
	{
		::TYPE t1 = 0;
		::g ( );
		typename B<T>::TYPE t2 = 0;
		this->g ( );
	}
};

class E : C
{
	void f1 ( )
	{
		TYPE t = 0;
		g ( );
		// A a = a();
		// a->f1();
	}
	void f2 ( )
	{
		::TYPE t1 = 0;
		::g ( );
		// typename B<T>::TYPE t2 = 0;	// error
		// this->g ( ); 		// error (???)
	}
};