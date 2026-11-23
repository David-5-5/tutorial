#include <bits/stdc++.h>
using namespace std;

class FooBar {
private:
    int n;
    mutex mtx;
    condition_variable cv;
    int turn = 0;      // 0: hello 线程，1: world 线程
public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [&]{return turn == 0;});
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            turn = 1;
            cv.notify_all();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [&]{return turn == 1;});
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            turn = 0;
            cv.notify_all();
        }
    }
};