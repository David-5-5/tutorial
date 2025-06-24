#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.1 堆 - 基础
class SeatManager {
private:
    int thres = 1;
    priority_queue<int, vector<int>, greater<>> pq;
public:
    SeatManager(int n) {
        // 类似于 2336 中 thres 做法
    }
    
    int reserve() {
        if (pq.empty()) {
            return thres ++;
        }
        int val = pq.top();
        pq.pop();
        return val;
    }
    
    void unreserve(int seatNumber) {
        if (seatNumber < thres) pq.push(seatNumber);
    }
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */