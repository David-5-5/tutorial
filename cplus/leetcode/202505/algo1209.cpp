#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.3 邻项消除
class Solution {
public:
    string removeDuplicates(string s, int k) {
        // 自行解答
        vector<pair<int,int>> st;

        for (auto& ch : s) {
            if (st.empty() || st.back().first != ch) {
                st.push_back({ch, 1});
            } else {
                int cnt = st.back().second + 1;
                if (cnt == k) {
                    for (int _=1; _<k; ++_) st.pop_back();
                } else {
                    st.push_back({ch, cnt});
                }
            }
        }

        string ans = "";
        for (auto& [ch, _] : st) ans += ch;
        return ans;
    }
};