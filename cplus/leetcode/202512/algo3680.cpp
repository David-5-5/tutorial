#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 随机算法 - 6.1 随机数
class Solution {
public:
    vector<vector<int>> generateSchedule(int n) {
        // 参考题解 学习随机方法构造
        if (n < 5) return {};

        auto generate = [&] (vector<vector<int>> p) -> vector<vector<int>> {
            vector<vector<int>> ans;
            ans.push_back(p.back()); p.pop_back();
            while (!p.empty()) {
                bool found = false;
                for (int i=p.size()-1; i>=0; --i) {
                    if (p[i][0] != ans.back()[0] && p[i][0] != ans.back()[1] && 
                        p[i][1] != ans.back()[0] && p[i][1] != ans.back()[1]) {
                        ans.push_back(p[i]);
                        p.erase(p.begin() + i);
                        found = true; break; // next 
                    }
                }
                if (!found) return {};
            }
            return ans;
        };

        vector<vector<int>> perm;
        mt19937 gen(rand() + chrono::steady_clock::now().time_since_epoch().count());
        for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) if (i!=j) perm.push_back({i, j});
        while (true) {
            shuffle(perm.begin(), perm.end(), gen);
            vector<vector<int>> ans = generate(perm);
            if (!ans.empty()) return ans;
        }

        return {};    
    }
};