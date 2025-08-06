#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 8.3 树状数组和线段树 - 线段树（无区间更新）
class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        // 分治 确定 l 后区间 [l, r] 的区间积mul[l..] %k 的个数为 r - l + 1 个，分别为 l 到 l,l+1, ... r
        // 区间的数据结构定义如下 {mul%k, array<int, k>}, 1,区间积模 k, 2,区间内每个值的出现次数， r-l+1 个计数，值域为 0~k-1
        // left = [l,m], right = [m+1,r]
        // left {left_mul, array{}}, rigth {right_mul, array{}}
        // new_val.mul = left_mul * right_mul % k
        // new_val.array<..> =  left.array<..>
        // new_val.array[left_mul*i] += right.array[i]; 
        // right 中的 r-m 个计数不是 右区间m+1,...r 一个个计算，而是乘以 [0,...k-1] 的计数结果
        using T = pair<int, array<int, 5>>;
        int n = nums.size();
        // 参考 oi-wiki 线段树模板

        vector<pair<int, array<int, 5>>> tree(4*n);
                
        auto merge = [&] (T a, T b) -> T {  
            for (int i=0; i<k; ++i) 
                a.second[a.first*i%k] += b.second[i];
            return {a.first*b.first%k, a.second};
        };

        auto new_val = [&] (int val) -> T {
            array<int, 5> cnt{}; cnt[val%k]=1;
            return {val%k, cnt};
        };        

        // build 性能优化 update
        auto build = [&](this auto&& build, int start, int end, int p) -> void {
            if (start == end) {
                tree[p] = new_val(nums[start]); return;
            }
            int m = start + ((end - start) >> 1);
            build(start, m, p*2+1);
            build(m + 1, end, p*2+2);
            tree[p] = merge(tree[p*2+1], tree[p*2+2]);
        };

        auto update = [&] (this auto&& update, int l, int val, int start, int end, int p) -> void {
            if (l == start and l == end) {
                tree[p] = new_val(val); return;
            }
            int m = start + ((end - start) >> 1);

            if (l <= m)
                update(l, val, start, m, p*2+1);
            else
                update(l, val, m + 1, end, p*2+2);
            
            tree[p] = merge(tree[p*2+1], tree[p*2+2]);
            // tree[p].second[tree[p].first] ++;
        };

        auto query = [&] (this auto&& query, int l, int r, int start, int end, int p) -> T {
            if (l <= start && end <= r) {
                return tree[p];
            }
            int m = start + ((end - start) >> 1);

            if (r <= m)
                return query(l, r, start, m, p*2+1);
            if (l > m)
                return query(l, r, m + 1, end, p*2+2);
            auto left = query(l, r, start, m, p*2+1);
            auto right = query(l, r, m + 1, end, p*2+2);
            return merge(left, right);
        };
        // 参考 oi-wiki 线段树模板
        // for (int i=0; i<n; ++i) update(i, nums[i], 0, n-1, 0);
        build(0, n-1, 0);
        
        vector<int> ans;
        for (auto& q : queries) {
            int inx = q[0], val = q[1], l = q[2], x = q[3];
            update(inx, val, 0, n-1, 0);
            ans.push_back(query(l, n-1, 0, n-1, 0).second[x]);
        }
        return ans;
    }
};


int main() {
    vector<int> nums = {1,2,4,8,16,32};
    vector<vector<int>> queries = {{0,2,0,2}, {0,2,0,1}};
    Solution s;
    auto res = s.resultArray(nums, 4, queries);
    for (auto& e : res) cout << e << " ";
    return 0;
}