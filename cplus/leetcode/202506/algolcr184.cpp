#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 4.4 单调队列
class Checkout {
private:
    queue<int> que;
    priority_queue<int, vector<int>, greater<>> pq;
    unordered_map<int, int> cnt;
public:
    Checkout() {        
    }
    
    int get_max() {
        while (!pq.empty() && cnt[pq.top()] == 0) {
            pq.pop();
        }
        if (pq.empty()) return -1;
        else pq.top();
    }

    
    void add(int value) {
        que.push(value);

        // if (!cnt.count(value)) pq.push(value); // it's wrong
        if (cnt[value]==0) pq.push(value);
        cnt[value] ++;
    }
    
    int remove() {
        if (que.empty()) return -1;
        int value = que.front();
        cnt[value] --;
        que.pop();
        return value;
    }
};

/**
 * Your Checkout object will be instantiated and called as such:
 * Checkout* obj = new Checkout();
 * int param_1 = obj->get_max();
 * obj->add(value);
 * int param_3 = obj->remove();
 */