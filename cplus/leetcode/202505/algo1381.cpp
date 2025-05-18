#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.2 进阶
class CustomStack {
private:
    vector<int> st;
    int capacity;
public:
    CustomStack(int maxSize) {
        capacity = maxSize;
    }
    
    void push(int x) {
        if (st.size() < capacity) st.push_back(x);
    }
    
    int pop() {
        if (st.size()) {
            int val = st.back();
            st.pop_back();
            return val;
        } else return -1;
    }
    
    void increment(int k, int val) {
        for (int i=0; i<min(k, (int)st.size()); ++i) st[i] += val;
    }
};


class CustomStack {
private:
    vector<int> st, add;
    int top = -1;
public:
    CustomStack(int maxSize) {
        st.assign(maxSize, 0), add.assign(maxSize, 0);
    }
    
    void push(int x) {
        if (top+1 < st.size())
            st[++top] = x;
    }
    
    int pop() {
        if (top < 0) return -1;
        int val = st[top] + add[top];
        if (top) {
            add[top-1] += add[top];
        }
        add[top--] = 0;
        return val;
    }
    
    void increment(int k, int val) {
        if (top>=0)
            add[min(k-1, top)] += val;
    }
};
/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */