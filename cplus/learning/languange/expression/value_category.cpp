#include <type_traits>
#include <utility>
#include <iostream>

template <class T> struct is_prvalue : std::true_type {};
template <class T> struct is_prvalue<T&> : std::false_type {};
template <class T> struct is_prvalue<T&&> : std::false_type {};
 
template <class T> struct is_lvalue : std::false_type {};
template <class T> struct is_lvalue<T&> : std::true_type {};
template <class T> struct is_lvalue<T&&> : std::false_type {};
 
template <class T> struct is_xvalue : std::false_type {};
template <class T> struct is_xvalue<T&> : std::false_type {};
template <class T> struct is_xvalue<T&&> : std::true_type {};
 
 struct S
{
    S() : m{42} {}
    S(int a) : m{a} {}
    int m;
};
 
void rvalue_sample_1(){
    S s;
    // Expression `S{}` is prvalue
    // May appear on the right-hand side of an assignment expression
    s = S{};
    std::cout << s.m << '\n';

    // Expression `S{}` is prvalue
    // Can be used on the left-hand side too
    std::cout << (S{} = S{7}).m << '\n';
};


void rvalue_sample_2() {
    int a{42};
    int& b{a};
    int&& r{std::move(a)};
 
    // Expression `42` is prvalue
    static_assert(is_prvalue<decltype((42))>::value);
 
    // Expression `a` is lvalue
    static_assert(is_lvalue<decltype((a))>::value);
 
    // Expression `b` is lvalue
    static_assert(is_lvalue<decltype((b))>::value);
 
    // Expression `std::move(a)` is xvalue
    static_assert(is_xvalue<decltype((std::move(a)))>::value);
 
    // Type of variable `r` is rvalue reference
    static_assert(std::is_rvalue_reference<decltype(r)>::value);
 
    // Type of variable `b` is lvalue reference
    static_assert(std::is_lvalue_reference<decltype(b)>::value);
 
    // Expression `r` is lvalue
    static_assert(is_lvalue<decltype((r))>::value);
}

struct A
{
    int m;
};
 
A&& operator+(A, A);
A&& f();
 
void xvalue_sample()
{
    A a;
    A&& ar = static_cast<A&&>(a);
 
    // Function call with return type rvalue reference is xvalue
    static_assert(is_xvalue<decltype( (f()) )>::value);
 
    // Member of object expression, object is xvalue, `m` is a non-static data member
    static_assert(is_xvalue<decltype( (f().m) )>::value);
 
    // A cast expression to rvalue reference
    static_assert(is_xvalue<decltype( (static_cast<A&&>(a)) )>::value);
 
    // Operator expression, whose return type is rvalue reference to object
    static_assert(is_xvalue<decltype( (a + a) )>::value);
 
    // Expression `ar` is lvalue, `&ar` is valid
    static_assert(is_lvalue<decltype( (ar) )>::value);
    [[maybe_unused]] A* ap = &ar;
}


int main(){
    rvalue_sample_1();

    rvalue_sample_2();

    xvalue_sample();
}