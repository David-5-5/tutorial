#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.7 单调栈 - 基础
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        // 参考题解，看错题目了，弄了半天
        vector<double> st;  // 单调栈 递减数据
        int ans = 0, n = position.size(), ids[n];
        iota(ids, ids+n, 0);
        sort(ids, ids+n, [&](int i, int j){   // 稳定排序
            return position[i] > position[j];
        }); 

        for (int i=0; i<n; ++i) {
            int id = ids[i];
            double t = 1.0 * (target - position[id]) / speed[id];
            while (st.size() && st.back() < t) {
                st.pop_back();
            }

            ans += st.size()?0:1;
            st.push_back(t);
        }
        
        return ans;
    }
};