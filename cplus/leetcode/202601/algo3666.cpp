#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.8 其他
class Solution {
public:
    int minOperations(string s, int k) {
        int n = s.size(), z = 0; for (auto& ch:s) if (ch=='0') z++;
        if (z % 2 == 1 && k % 2 == 0) return -1; // 剪枝
        set<int> vis[2]; 
        for (int i=0; i<=n; ++i) {
            if (i==z) continue;
            vis[i%2].insert(i);     // 一定要分奇偶，否则超时!!!!
        }
        
        vector<int> q = {z}; int step = 0;
        while (!q.empty()) {
            vector<int> nxt;
            for (auto& u: q) {
                if (u == 0) return step;
                int mn = max(0, k+u-n), mx = min(k, u);
                int z_lower = u + k - 2 * mx, z_upper = u + k - 2 * mn;
                auto &s = vis[(u+k)%2]; auto it = s.lower_bound(z_lower);
                while (it!=s.end() && *it <= z_upper) {
                    auto cur = it; it = next(it);
                    nxt.emplace_back(*cur);
                    s.erase(cur);
                }
            }
            q = move(nxt); step ++;
        } 
        return -1;
    }

 
};

int main() {
    cout << Solution().minOperations("101", 2) << endl;
}