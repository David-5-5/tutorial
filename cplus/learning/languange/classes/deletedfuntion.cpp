
// C++ program to disable the usage of
// copy-constructor using delete operator
#include <iostream>
using namespace std;
 
class A {
public:
    A(int x): a(x)
    {
    }
     
    // Delete the copy constructor
    A(const A&) = delete; 
     
    // Delete the copy assignment operator
    A& operator=(const A&) = delete; 
    int a;
};

class B {
public:
    B(int x): b(x)
    {
    }
    int b;
};

int main()
{
    A a1(1), a2(2), a3(3);
    B b1(1), b2(2), b3(3);
     
    // Error, the usage of the copy
    // assignment operator is disabled
    // a1 = a2;
    b1 = b2;
     
    // Error, the usage of the
    // copy constructor is disabled
    // a3 = A(a2);
    b3 = B(b2);
    return 0;
}