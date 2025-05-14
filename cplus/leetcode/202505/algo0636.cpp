#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.2 进阶
class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        // 自行解答
        vector<int> ans(n);
        vector<pair<int,int>> st;

        for (auto& log : logs) {
            int p0 = log.find(':'), p1 = log.find(':', p0+1);
            int i = stoi(log.substr(0, p0)), time = stoi(log.substr(p1+1));

            if (p1 - p0 == 6) {   // start
                if (st.size()) {
                    int slice = time - st.back().second;
                    ans[st.back().first] += slice;
                    st.back().second = time;
                }
                st.push_back({i, time});
            } else {              // end
                int slice = time - st.back().second + 1;
                ans[st.back().first] += slice;
                st.pop_back();
                if (st.size()) st.back().second = time+1;
            }

        }

        return ans;

    }
};