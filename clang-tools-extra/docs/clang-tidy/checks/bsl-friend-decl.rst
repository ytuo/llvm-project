.. title:: clang-tidy - bsl-friend-decl

bsl-friend-decl
===============

Warns on friend declarations.

Example:

.. code-block:: c++

    class C;

    class A {
    public:
        A& operator+=(A const& rhs);

        // Warns on two lines below
        friend A const operator-(A const& lhs, A const& rhs);
        friend class C;
    };
