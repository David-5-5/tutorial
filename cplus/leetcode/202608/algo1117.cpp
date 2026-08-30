#include <bits/stdc++.h>
#include <barrier>
using namespace std;

class H2O {
private:
    // mutex mtx;
    counting_semaphore<2> sem_h{2};
    counting_semaphore<1> sem_o{1};
    barrier<> b{3};    
public:
    H2O() {
        
    }

    void hydrogen(function<void()> releaseHydrogen) {
        sem_h.acquire();
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        b.arrive_and_wait();
        sem_h.release();
    }

    void oxygen(function<void()> releaseOxygen) {
        // lock_guard lock{mtx};
        sem_o.acquire();
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        b.arrive_and_wait();
        sem_o.release();
    }
};