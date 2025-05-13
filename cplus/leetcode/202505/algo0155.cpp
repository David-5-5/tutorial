#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.2 进阶
class MinStack {
private:
    stack<int> st;
    stack<int> min_st;
public:
    MinStack() {
    }
    
    void push(int val) {
        int mn = min_st.size()?min(min_st.top(), val):val;
        st.push(val);
        min_st.push(mn);
    }
    
    void pop() {
        st.pop();
        min_st.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return min_st.top();
    }
};

// using vector
class MinStack {
private:
    vector<int> st;
    vector<int> min_st;
public:
    MinStack() {
    }
    
    void push(int val) {
        int mn = min_st.size()?min(min_st.back(), val):val;
        st.push_back(val);
        min_st.push_back(mn);
    }
    
    void pop() {
        st.pop_back();
        min_st.pop_back();
    }
    
    int top() {
        return st.back();
    }
    
    int getMin() {
        return min_st.back();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */