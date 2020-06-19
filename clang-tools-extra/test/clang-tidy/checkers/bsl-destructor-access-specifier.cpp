// RUN: %check_clang_tidy %s bsl-destructor-access-specifier %t

class A
{
  public:
    ~A() // Non-compliant
    {
    }
};

class B : public A
{
};

class C
{
  public:
    virtual ~C() // Compliant
    {
    }
};

class D : public C
{
};

class E
{
  protected:
    ~E(); // Compliant
};


class F  		// non-compliant
{
public:
	~F() = default;
};

class G final	// compliant
{
public:
	~G() = default;
};

class H		// compliant
{
public:
	virtual ~H() = default;
};

class I: public F
{
};

class J: public H {};


template <typename T>
class X {
private:
    T t;
public:
    T get_t() { return t; }
    ~X() = default; // non-compliant, class is not final
};

int foo()
{
    X<int> x;
   return x.get_t();
}