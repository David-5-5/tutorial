#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 4.2 队列 - 设计
class FrontMiddleBackQueue {
private:
    vector<int> fmb;
public:
    FrontMiddleBackQueue() {
        
    }
    
    void pushFront(int val) {
        fmb.insert(fmb.begin(), val);
    }
    
    void pushMiddle(int val) {
        int pos = fmb.size() / 2;
        fmb.insert(fmb.begin()+pos, val);
    }
    
    void pushBack(int val) {
        fmb.push_back(val);
    }
    
    int popFront() {
        if (fmb.empty()) return -1;
        int val = fmb.front();
        fmb.erase(fmb.begin());
        return val;
    }
    
    int popMiddle() {
        if (fmb.empty()) return -1;
        int pos = (fmb.size()-1) / 2;
        int val = *(fmb.data() + pos);
        fmb.erase(fmb.begin() + pos);
        return val;
    }
    
    int popBack() {
        if (fmb.empty()) return -1;
        int val = fmb.back();
        fmb.pop_back();
        return val;
    }
};

/**
 * Your FrontMiddleBackQueue object will be instantiated and called as such:
 * FrontMiddleBackQueue* obj = new FrontMiddleBackQueue();
 * obj->pushFront(val);
 * obj->pushMiddle(val);
 * obj->pushBack(val);
 * int param_4 = obj->popFront();
 * int param_5 = obj->popMiddle();
 * int param_6 = obj->popBack();
 */