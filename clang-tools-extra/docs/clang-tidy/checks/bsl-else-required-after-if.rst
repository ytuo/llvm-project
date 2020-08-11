.. title:: clang-tidy - bsl-else-required-after-if

bsl-else-required-after-if
==========================

Warns if the use of else is incorrect, which could cause MC/DC testing to
no longer be verified using line coverage tools. There are different situations
that could cause this including:
- if you have an if with no else
- if you have an if whose body has a return/continue/break and a "next line"
  is missing.
- if you have an if whose body has another if/else, both of which return.

For the typical if statement:

.. code-block:: c++

  if (x) {
      do_something();
  }

In the code above, we have no way of knowing if the "else" was taken without
relying on the compilers to accurately record this information in a coverage
report, which tends to be buggy. Instead, if we did the following:

.. code-block:: c++

  if (x) {
      do_something();
  }
  else {
      bsl::touch();
  }

We can prove that the "else" condition was taken during testing with simple
line coverage. The bsl::touch() is used to ensure that something is there to
execute, which will ensure that a line of code shows up in the coverage
report.

In some cases, "else" is not only not needed, but is not desired as it results
in extra noise that could be avoided. For example:

.. code-block:: c++

  while (true) {
      if (x) {
          break;
      }

      bsl::touch();
  }

In the example above, we can prove that the "else" condition was taken because
the bsl::touch() will not execute unless the "else" condition was successfully
taken. For line coverage to work, a line of code after this if statement is
needed. In the example above, we use a bsl::touch() as there is nothing else
to do, but if additional code is added, the bsl::touch() is not needed.

Finally, we ensure that the else is not provided, which also ensures these
checks works as expected, and it also reduces noise. For example:

.. code-block:: c++

  while (true) {
      if (x) {
          break;
      }
      else {
          bsl::touch();
      }
  }

should be changed to:

.. code-block:: c++

  while (true) {
      if (x) {
          break;
      }

      bsl::touch();
  }

This is because the else is not needed as explained above, and adding the else
makes the implementation of this check far more complicated.

