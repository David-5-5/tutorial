#include <bits/stdc++.h>
using namespace std;

// 一般树 - 3.7 DFS 时间戳
class Solution {
public:
    vector<bool> findAnswer(vector<int>& parent, string s) {
        // 自行解答，超时
        int n = parent.size();
        vector<vector<int>> g(n, vector<int>());
        for (int i=1; i<n; ++i) g[parent[i]].push_back(i);

        unordered_map<long, bool> memo;
        

        int clock = 0; vector<bool> ans(n); string dfs_str = "";
        auto is_pal = [&] (this auto&& is_pal, int l, int r) -> bool {
            if (l>r) return true;
            long mask = (long) l << 32 | r;
            if (memo.count(mask)) return memo[mask];
            if (dfs_str[l]!=dfs_str[r]) return memo[mask] = false;
            else return is_pal(l+1, r-1);
        };

        auto dfs = [&] (this auto&& dfs, int u) -> void {
            int in_clock = dfs_str.length();
            for (auto & v: g[u]) {
                dfs(v);
            }
            dfs_str.push_back(s[u]);
            auto out_clock = dfs_str.length()-1;
            ans[u] = is_pal(in_clock, out_clock);
        };
        dfs(0);  return ans;     
    }


    vector<bool> findAnswer2(vector<int>& parent, string s) {
        // 自行解答, manacher 算法求解区间字符串是否回文
        int n = parent.size();
        vector<vector<int>> g(n, vector<int>());
        for (int i=1; i<n; ++i) g[parent[i]].push_back(i);

        vector<pair<int,int>> intervals(n);

        int clock = 0; vector<bool> ans(n); string dfs_str = "";

        auto dfs = [&] (this auto&& dfs, int u) -> void {
            int in_clock = dfs_str.length();
            for (auto & v: g[u]) {
                dfs(v);
            }
            dfs_str.push_back(s[u]);
            intervals[u] = {in_clock, dfs_str.length()-1};
        };
        dfs(0);
        
        // BEGIN Manacher 马拉车 模板
        vector<int> d1(n);
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
            while (0 <= i - k && i + k < n && dfs_str[i - k] == dfs_str[i + k]) {
                k++;
            }
            d1[i] = k--;
            if (i + k > r) {
                l = i - k;
                r = i + k;
            }
        }
        vector<int> d2(n);
            for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
            while (0 <= i - k - 1 && i + k < n && dfs_str[i - k - 1] == dfs_str[i + k]) {
                k++;
            }
            d2[i] = k--;
            if (i + k > r) {
                l = i - k - 1;
                r = i + k;
            }
        }
        // END manacher 模板
        for (int i=0; i<n; ++i) {
            auto & [l, r] = intervals[i];
            if ((r - l + 1) % 2) {
                ans[i] = d1[(r+l)/2] > (r - l) / 2;
            } else {
                ans[i] = d2[(r+l+1)/2] >= (r - l + 1) / 2;
            }
        }
        return ans;
 
    }    
};

int main() {
    vector<int> parents = {-1,0,0,1,1,2};
    string s = "aababa";
    Solution().findAnswer2(parents, s);
}