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

clewass C
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

