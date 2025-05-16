#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.2 进阶
class DinnerPlates {
private:
    vector<stack<int>> plates;

    priority_queue<int, vector<int>, greater<>> forpush;
    int capacity;

public:
    // 自行解答
    DinnerPlates(int capacity) {
        this->capacity = capacity;
        plates.emplace_back();
    }
    
    void push(int val) {
        while (forpush.size()) {
            int inx = forpush.top();
            if (inx>=plates.size() || plates[inx].size()==capacity){
                // remove invalid inx
                forpush.pop();
            } else break;
        }
        if (forpush.size()) {
            int i = forpush.top();
            plates[i].push(val);
            if (plates[i].size() == capacity) forpush.pop();
        }else {
            plates.back().push(val);
            if (plates.back().size() == capacity) plates.emplace_back();
        }
    }
    
    int pop() {
        while (plates.back().size() == 0 && plates.size()>1) {
            plates.pop_back();
        }
        if (plates.back().size() == 0) return -1;
        else {
            int val = plates.back().top();
            plates.back().pop();
            return val;
        }
    }
    
    int popAtStack(int index) {
        if (index+1 == plates.size()) return pop();
        
        if (index < plates.size() && plates[index].size()) {
            if (plates[index].size() == capacity) forpush.push(index);
            int val = plates[index].top();
            plates[index].pop();
            return val;
        }

        return -1;
    }
};

/**
 * Your DinnerPlates object will be instantiated and called as such:
 * DinnerPlates* obj = new DinnerPlates(capacity);
 * obj->push(val);
 * int param_2 = obj->pop();
 * int param_3 = obj->popAtStack(index);
 */