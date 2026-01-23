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

    int minOperations2(string s, int k) {
        int n = s.size(), z = 0; for (auto& ch:s) if (ch=='0') z++;
        set<int> vis[2]; 
        for (int i=0; i<=n; ++i) {
            if (i==z) continue;
            vis[i%2].insert(i);
        }
        vector<int> q = {z}; int step = 0;
        while (!q.empty()) {
            vector<int> nxt;
            for (auto& u: q) {
                if (u == 0) return step;
                int mn = max(0, k+u-n), mx = min(k, u);
                int z_lower = u + k - 2 * mx, z_upper = u + k - 2 * mn;
                auto &s = vis[z_lower%2];
                // 相对于 while, for 循环特别简洁
                for (auto it = s.lower_bound(z_lower); it!=s.end() && *it<=z_upper; it=s.erase(it))
                    nxt.emplace_back(*it);

            }
            q = move(nxt); step ++;
        } 
        return -1;
    }    

    int minOperations3(string s, int k) {
        // 参考题解 数学方法 隐式应用 Gale-Ryser 定理
        int n = s.size(), z = 0; for (auto& ch:s) if (ch=='0') z++;
        if (z == 0) return 0;
        if (n == k) return (z==n)?1:-1;

        int ans = INT_MAX;
        if (z % 2 == 0) {   // m 为偶数
            int m = max((z+k-1)/k, (z+n-k-1)/(n-k));
            ans = min(ans, m + m % 2);
        }

        if (z % 2 == k % 2) {   // m 为奇数
            int m = max((z+k-1)/k, (n-z+n-k-1)/(n-k));
            ans = min(ans, m + (m % 2==0));
        }

        return ans < INT_MAX? ans: -1;
    }
};

int main() {
    cout << Solution().minOperations("101", 2) << endl;
}