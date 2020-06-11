// RUN: %check_clang_tidy %s bsl-non-pod-classdef %t

class N { // neither trivial nor standard-
   private: 
    int i;
   public: 
    int j;
    // virtual ~N();
};

struct T { // trivial but not standard-layout
public:
    int i;
    int j;
};

struct SL { // standard-layout but not trivial
private:

    int i;
    int j;
    // ~SL();
};

N n;
T t;
SL sl;

// class NonPOD1 {

// };

// class POD1 {

// };

// /// @brief POD type
// struct foo final
// { 
//     bool data;
// };
// /// @brief non-POD type
// class non_pod_foo final
// { 
// public:
//     bool data{true};
// };
// /// @brief non-compliant - defines global and initializes at runtime
// foo g_bar1{};
// /// @brief compliant - defines global and initializes at compile time
// foo g_bar2;
/// @brief compliant - defines global and initializes at compile time 
///    using constinit. Note that because this is a non-POD type, use 
///    of the {} is not needed, but is fine since this was paired with 
///    constinit. 
// constinit non_pod_foo g_bar3{};
// /// @brief non-compliant - defines static and initializes at runtime
// /// @return a reference to foo
// [[nodiscard]] foo const &
// get_bar1() noexcept 
// {
//     static foo s_bar1{};
//     return s_bar1;
// }
// /// @brief compliant - defines static local and initializes at compile time
// /// @return a reference to foo
// [[nodiscard]] foo const &
// get_bar2() noexcept 
// {
//     static foo s_bar2;
//     return s_bar2;
// }
// /// @brief compliant - defines static local and initializes at compile time 
// ///    using constinit. Note that because this is a non-POD type, use 
// ///    of the {} is not needed, but is fine since this was paired with 
// ///    constinit. 
// /// @return a reference to non_pod_foo
// [[nodiscard]] non_pod_foo const &
// get_bar3() noexcept 
// {
//     constinit static non_pod_foo s_bar3{};
//     return s_bar3;
// }
// /// @brief a function that does something
// constexpr void
// do_something() noexcept 
// {
//     foo bar1; /// non-compliant - foo is POD but not initialized
//     foo bar2{}; /// compliant - foo is POD and is explicitly initialized
//     non_pod_foo bar2; /// compliant - non_pod_foo is a non-POD.
//     non_pod_foo bar3{}; /// compliant - non_pod_foo is a non-POD.
//     return s_bar2;
// }