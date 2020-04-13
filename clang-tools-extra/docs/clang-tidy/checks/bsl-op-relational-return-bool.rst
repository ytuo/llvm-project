.. title:: clang-tidy - bsl-op-relational-return-bool

bsl-op-relational-return-bool
=============================

Warns if a comparison operator doesn't have boolean return type.

Example:

.. code-block:: c++

  class A {
  public:
      // Warns on four lines below
      long operator<(A const& rhs);
      int operator!=(A const& rhs);
      short operator>=(A const& rhs);
      long operator<=(A const& rhs);

      int x;
  };


  // Warns on two lines below
  int operator<(A lhs, A rhs);
  int operator>(A lhs, A rhs)
  {
      return -1;
  }

  // No warning here
  bool operator==(A lhs, A rhs)
  {
      return lhs.x == rhs.x;
  }
