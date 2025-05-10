#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.1 基础
class BrowserHistory {
private:
    vector<string> st;
    int inx = 0;
public:
    // 自行解答
    BrowserHistory(string homepage) {
        st.push_back(homepage);
        inx = st.size()-1;
    }
    
    void visit(string url) {
        st.resize(inx+1);
        st.push_back(url);
        inx = st.size() - 1;
    }
    
    string back(int steps) {
        inx = max(0, inx-steps);
        return st[inx];        
    }
    
    string forward(int steps) {
        inx = min(steps+inx, (int)st.size()-1);
        return st[inx];
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */