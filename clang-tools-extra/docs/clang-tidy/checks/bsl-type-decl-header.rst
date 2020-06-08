.. title:: clang-tidy - bsl-type-decl-header

bsl-type-decl-header
====================

Checks that type name declared in header file identical to file name.

Examples:

.. code-block:: c++

  // Given header file name BSLTypeDeclHeader.hpp

  class BSLTypeDeclHeader {
    struct Inner {};

    union InnerUnion {
      enum InnerEnum { a };
    };
  };	// All compliant, including nested types

  class NotBSLTypeDeclHeader {
    struct Inner {};
  };	// Non-compliant
