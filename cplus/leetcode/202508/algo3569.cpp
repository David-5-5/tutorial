#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+1;
bool is_prime[N];
int init = [] {
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = false; is_prime[1] = false;
    for (int i = 2; i <= sqrt(N); ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return 0;
}();

// 常用数据结构 - 8.4 Lazy 线段树（有区间更新）
class Solution {
public:
    vector<int> maximumCount(vector<int>& nums, vector<vector<int>>& queries) {
        // 参考题解 - 
        int n = nums.size();
        // 参考 oi-wiki 线段树模板 - 区间更新 最大值
        vector<int> tree(4 * n);
        vector<int> tp(4 * n);     // 支持懒标记

        // 下推懒标记
        auto pushdown = [&] (this auto&& pushdown, int s, int t, int p) -> void{
            if (s == t) return;  // 叶子节点无需下推
            int m = s + ((t - s) >> 1);

            // 更新左子树
            tree[p * 2 + 1] += tp[p]; tp[p * 2 + 1] += tp[p];
            // 更新右子树
            tree[p * 2 + 2] += tp[p]; tp[p * 2 + 2] += tp[p];
            // 清空当前节点懒标记
            tp[p] = 0;
        };

        // 区间更新：[l, r] 区间增加 value
        auto update = [&](this auto&& update, int l, int r, int value, int s, int t, int p) -> void{
            if (l <= s && t <= r) {
                // 当前区间完全在更新范围内
                tree[p] += value;            // 区间 + val
                if (s != t)  tp[p] += value; // 非叶子节点才需要标记
                return;
            }
            // 下推懒标记
            if (tp[p] != 0) pushdown(s, t, p);

            int m = s + ((t - s) >> 1);
            // 递归更新左子树
            if (l <= m)  update(l, r, value, s, m, p * 2 + 1);
            // 递归更新右子树
            if (r > m) update(l, r, value, m + 1, t, p * 2 + 2);
            // 更新当前节点值
            tree[p] = max(tree[p * 2 + 1], tree[p * 2 + 2]);
        };
        // 参考 oi-wiki 线段树模板 - 区间更新 最大值

        unordered_map<int, set<int>> mp;
        for (int i = 0; i < n; ++i) if (is_prime[nums[i]]) mp[nums[i]].insert(i);
        for (auto& [x, st]: mp) {
            int l = *st.begin(), r = *st.rbegin();
            if (l != r) update(l, r, 1, 0, n-1, 0); // 初始化
        }
        
        vector<int> ans;
        for (auto& q : queries) {
            auto inx = q[0], val = q[1];
            if (nums[inx] != val) {
                if (is_prime[nums[inx]]) {
                    int l = *mp[nums[inx]].begin(), r = *mp[nums[inx]].rbegin();
                    mp[nums[inx]].erase(inx);
                    if (mp[nums[inx]].size()==0) mp.erase(nums[inx]);
                    else {
                        int n_l = *mp[nums[inx]].begin(), n_r = *mp[nums[inx]].rbegin();
                        if (l != n_l || r != n_r) {
                            update(l, r, -1, 0, n-1, 0);
                            if (n_l != n_r) update(n_l, n_r, 1, 0, n-1, 0);
                        }
                    }
                }
                nums[inx] = val;
                if (is_prime[val]) {
                    if (!mp.count(val))
                        mp[val].insert(inx);
                    else {
                        int l = *mp[nums[inx]].begin(), r = *mp[nums[inx]].rbegin();
                        mp[nums[inx]].insert(inx);
                        int n_l = *mp[nums[inx]].begin(), n_r = *mp[nums[inx]].rbegin();
                   
                        if (l != n_l || r != n_r) {
                            if (l!=r) update(l, r, -1, 0, n-1, 0);
                            if (n_l != n_r) update(n_l, n_r, 1, 0, n-1, 0);
                        }                
                        
                    }
                }
            }
            ans.push_back(tree[0] + (int)mp.size());
        }
        
        return ans;
    }


};

int main() {
    vector<int> nums = {2,2,3};
    vector<vector<int>> queries = {{1,63},{2,3},{2,25}};
    Solution().maximumCount(nums, queries);
}