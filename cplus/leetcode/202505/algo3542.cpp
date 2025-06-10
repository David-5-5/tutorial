#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.7 单调栈 - 扩展
class Solution {
public:
    int minOperations(vector<int>& nums) {
        // 栈 - 自行解答，有些脑筋急转弯
        int ans = 0;
        stack<int> st;      // 单调递减
        for (auto& v: nums) {
            while (st.size() && st.top()>v) 
                st.pop(), ans ++;
            if (v > 0 && (st.empty() || v>st.top()))
                st.push(v);  // 入栈元素不为 0 且不等于栈顶元素
        }

        return ans + st.size();  
    }
};