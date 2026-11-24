#include <bits/stdc++.h>
using namespace std;

class ZeroEvenOdd {
private:
    int n;
    mutex mtx;
    condition_variable cv;
    int turn = 2;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i++) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [&]{return turn == 2;});
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printNumber(0);
            turn = i % 2;
            cv.notify_all();
        }        
    }

    void even(function<void(int)> printNumber) {
        for (int i = 2; i <= n; i+=2) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [&]{return turn == 0;});
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printNumber(i);
            turn = 2;
            cv.notify_all();
        }           
    }

    void odd(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i+=2) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [&]{return turn == 1;});
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printNumber(i);
            turn = 2;
            cv.notify_all();
        }            
    }
};