#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.7 堆 - 对顶堆（滑动窗口第 K 小/大）
class MedianFinder {
private:
    priority_queue<int> left;                               // 大根
    priority_queue<int, vector<int>, greater<>> right;      // 小根
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        right.emplace(num);
        left.push(right.top()); right.pop();
        if (left.size()>right.size() + 1) {
            right.push(left.top()); left.pop();
        }
    }
    
    double findMedian() {
        if (left.size() == right.size()) {
            return (left.top() * 1.0 + right.top())/2;
        } return left.top();
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */