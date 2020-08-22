// RUN: %check_clang_tidy %s bsl-special-member-functions %t

class DefinesConstructor {
  DefinesConstructor();
};
// CHECK-MESSAGES: [[@LINE-3]]:7: warning: class 'DefinesConstructor' defines a default constructor but does not define a destructor, a copy constructor, a copy assignment operator, a move constructor or a move assignment operator [bsl-special-member-functions]

class DefinesDefaultedConstructor {
  DefinesDefaultedConstructor() = default;
};
// CHECK-MESSAGES: [[@LINE-3]]:7: warning: class 'DefinesDefaultedConstructor' defines a default constructor but does not define a destructor, a copy constructor, a copy assignment operator, a move constructor or a move assignment operator [bsl-special-member-functions]

class DefinesDestructor {
  ~DefinesDestructor();
};
// CHECK-MESSAGES: [[@LINE-3]]:7: warning: class 'DefinesDestructor' defines a non-default destructor but does not define a copy constructor, a copy assignment operator, a move constructor or a move assignment operator [bsl-special-member-functions]

class DefinesDefaultedDestructor {
  ~DefinesDefaultedDestructor() = default;
};
// CHECK-MESSAGES: [[@LINE-3]]:7: warning: class 'DefinesDefaultedDestructor' defines a default destructor but does not define a copy constructor, a copy assignment operator, a move constructor or a move assignment operator [bsl-special-member-functions]

class DefinesVirtualDestructor {
  virtual ~DefinesVirtualDestructor() = 0;
};

class DefinesDefaultedVirtualDestructor {
  virtual ~DefinesDefaultedVirtualDestructor() = default;
};

class DefinesCopyConstructor {
  DefinesCopyConstructor(const DefinesCopyConstructor &);
};
// CHECK-MESSAGES: [[@LINE-3]]:7: warning: class 'DefinesCopyConstructor' defines a copy constructor but does not define a destructor, a copy assignment operator, a move constructor or a move assignment operator [bsl-special-member-functions]

class DefinesDefaultedCopyConstructor {
  DefinesDefaultedCopyConstructor(const DefinesDefaultedCopyConstructor &) = default;
};
// CHECK-MESSAGES: [[@LINE-3]]:7: warning: class 'DefinesDefaultedCopyConstructor' defines a copy constructor but does not define a destructor, a copy assignment operator, a move constructor or a move assignment operator [bsl-special-member-functions]

class DefinesCopyAssignment {
  DefinesCopyAssignment &operator=(const DefinesCopyAssignment &);
};
// CHECK-MESSAGES: [[@LINE-3]]:7: warning: class 'DefinesCopyAssignment' defines a copy assignment operator but does not define a destructor, a copy constructor, a move constructor or a move assignment operator [bsl-special-member-functions]

class DefinesDefaultedCopyAssignment {
  DefinesDefaultedCopyAssignment &operator=(const DefinesDefaultedCopyAssignment &) = default;
};
// CHECK-MESSAGES: [[@LINE-3]]:7: warning: class 'DefinesDefaultedCopyAssignment' defines a copy assignment operator but does not define a destructor, a copy constructor, a move constructor or a move assignment operator [bsl-special-member-functions]

class DefinesMoveConstructor {
  DefinesMoveConstructor(DefinesMoveConstructor &&);
};
// CHECK-MESSAGES: [[@LINE-3]]:7: warning: class 'DefinesMoveConstructor' defines a move constructor but does not define a destructor, a copy constructor, a copy assignment operator or a move assignment operator [bsl-special-member-functions]

class DefinesDefaultedMoveConstructor {
  DefinesDefaultedMoveConstructor(DefinesDefaultedMoveConstructor &&) = default;
};
// CHECK-MESSAGES: [[@LINE-3]]:7: warning: class 'DefinesDefaultedMoveConstructor' defines a move constructor but does not define a destructor, a copy constructor, a copy assignment operator or a move assignment operator [bsl-special-member-functions]

class DefinesMoveAssignment {
  DefinesMoveAssignment &operator=(DefinesMoveAssignment &&);
};
// CHECK-MESSAGES: [[@LINE-3]]:7: warning: class 'DefinesMoveAssignment' defines a move assignment operator but does not define a destructor, a copy constructor, a copy assignment operator or a move constructor [bsl-special-member-functions]

class DefinesDefaultedMoveAssignment {
  DefinesDefaultedMoveAssignment &operator=(DefinesDefaultedMoveAssignment &&) = default;
};
// CHECK-MESSAGES: [[@LINE-3]]:7: warning: class 'DefinesDefaultedMoveAssignment' defines a move assignment operator but does not define a destructor, a copy constructor, a copy assignment operator or a move constructor [bsl-special-member-functions]


class DeleteConstructor {
  DeleteConstructor() = delete;
};
// CHECK-MESSAGES: [[@LINE-3]]:7: warning: class 'DeleteConstructor' defines a default constructor but does not define a destructor, a copy constructor, a copy assignment operator, a move constructor or a move assignment operator [bsl-special-member-functions]

class DeleteDestructor {
  ~DeleteDestructor() = delete;
};
// CHECK-MESSAGES: [[@LINE-3]]:7: warning: class 'DeleteDestructor' defines a non-default destructor but does not define a copy constructor, a copy assignment operator, a move constructor or a move assignment operator [bsl-special-member-functions]

class DeleteCopyConstructor {
  DeleteCopyConstructor(const DeleteCopyConstructor &) = delete;
};
// CHECK-MESSAGES: [[@LINE-3]]:7: warning: class 'DeleteCopyConstructor' defines a copy constructor but does not define a destructor, a copy assignment operator, a move constructor or a move assignment operator [bsl-special-member-functions]

class DeleteMoveConstructor {
  DeleteMoveConstructor(DeleteMoveConstructor &&) = delete;
};
// CHECK-MESSAGES: [[@LINE-3]]:7: warning: class 'DeleteMoveConstructor' defines a move constructor but does not define a destructor, a copy constructor, a copy assignment operator or a move assignment operator [bsl-special-member-functions]

class DeleteCopyAssignment {
  DeleteCopyAssignment &operator=(const DeleteCopyAssignment &) = delete;
};
// CHECK-MESSAGES: [[@LINE-3]]:7: warning: class 'DeleteCopyAssignment' defines a copy assignment operator but does not define a destructor, a copy constructor, a move constructor or a move assignment operator [bsl-special-member-functions]

class DeleteMoveAssignment {
  DeleteMoveAssignment &operator=(DeleteMoveAssignment &&) = delete;
};
// CHECK-MESSAGES: [[@LINE-3]]:7: warning: class 'DeleteMoveAssignment' defines a move assignment operator but does not define a destructor, a copy constructor, a copy assignment operator or a move constructor [bsl-special-member-functions]


class DefinesNothing {
};

class DefinesEverything {
  DefinesEverything(const DefinesEverything &);
  DefinesEverything &operator=(const DefinesEverything &);
  DefinesEverything(DefinesEverything &&);
  DefinesEverything &operator=(DefinesEverything &&);
  ~DefinesEverything();
};

class DeletesEverything {
  DeletesEverything(const DeletesEverything &) = delete;
  DeletesEverything &operator=(const DeletesEverything &) = delete;
  DeletesEverything(DeletesEverything &&) = delete;
  DeletesEverything &operator=(DeletesEverything &&) = delete;
  ~DeletesEverything() = delete;
};

class DeletesCopyDefaultsMove {
  DeletesCopyDefaultsMove(const DeletesCopyDefaultsMove &) = delete;
  DeletesCopyDefaultsMove &operator=(const DeletesCopyDefaultsMove &) = delete;
  DeletesCopyDefaultsMove(DeletesCopyDefaultsMove &&) = default;
  DeletesCopyDefaultsMove &operator=(DeletesCopyDefaultsMove &&) = default;
  ~DeletesCopyDefaultsMove() = default;
};

template <typename T>
struct TemplateClass {
  TemplateClass() = default;
  TemplateClass(const TemplateClass &);
  TemplateClass &operator=(const TemplateClass &);
  TemplateClass(TemplateClass &&);
  TemplateClass &operator=(TemplateClass &&);
  ~TemplateClass();
};

// Multiple instantiations of a class template will trigger multiple matches for defined special members.
// This should not cause problems.
TemplateClass<int> InstantiationWithInt;
TemplateClass<double> InstantiationWithDouble;
