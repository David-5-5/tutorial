#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.7 单调栈 - 基础
class StockSpanner {
private:
    stack<pair<int,int>> st;      // 单调栈 - 递减
    int d = 0;
public:
    // 自行解答
    StockSpanner() {
        // st.push({100001, 0});        // 哨兵
    }
    
    int next(int price) {
        while (st.size() && st.top().first < price) {
            st.pop();
        }
        int ans = ++d - (st.size()?st.top().second:0);
        // int ans = ++d - st.top().second; // 有哨兵写法
        st.push({price, d});
        return ans;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */