#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 10 莫队算法
class Solution {
public:
    vector<int> subarrayMajority(vector<int>& nums, vector<vector<int>>& queries) {
        // 参考题解 莫队算法
        int n = nums.size(), m = queries.size();

        unordered_map<int, int> cnt; int max_cnt = 0, min_val = 0;
        auto add = [&] ( int x) {
            int c = ++cnt[x];
            if (c > max_cnt) {
                max_cnt = c; min_val = x;
            } else if (c == max_cnt) {
                min_val = min(min_val, x);
            }
        };

        vector<int> ans(m, -1);
        int bs = ceil(n / sqrt(m * 2));

        struct Query {
            int bid, l, r, threshold, qid;
        };

        vector<Query> qs;
        for (int i=0; i<m; ++i) {
            auto & q = queries[i];
            int l = q[0], r = q[1] + 1, threshold = q[2]; // 左闭右开
            if (r - l > bs) {
                qs.emplace_back(l/ bs, l, r, threshold, i);
                continue;
            }
            for (int j=l; j<r; j++) {
                add(nums[j]);
            }
            if (max_cnt >= threshold) ans[i] = min_val;
            cnt.clear(); max_cnt = 0;
        }

        ranges::sort(qs, {}, [](auto & q) {return pair(q.bid, q.r);});

        // 莫队算法的关键步骤
        int r; 
        for (int i=0; i<qs.size(); ++i) {
            auto& q = qs[i];
            int l0 = (q.bid + 1) * bs;
            if (i == 0 || q.bid > qs[i-1].bid) {
                r = l0; cnt.clear(); max_cnt = 0;
            }
            for (; r < q.r; r++) add(nums[r]);
            int tmp_max_cnt = max_cnt, tmp_min_val = min_val;

            for (int j = q.l; j < l0; j++) add(nums[j]);

            if (max_cnt >= q.threshold) ans[q.qid] = min_val;

            max_cnt = tmp_max_cnt; min_val = tmp_min_val;
            for (int j=q.l; j<l0; j++) cnt[nums[j]] --;
        }

        return ans;
    }

    vector<int> subarrayMajority2(vector<int>& nums, vector<vector<int>>& queries) {
        // 参考题解 莫队算法 离散化优化
        int n = nums.size(), m = queries.size();
        vector<int> uni_arr = nums; ranges::sort(uni_arr);
        uni_arr.erase(ranges::unique(uni_arr).begin(), uni_arr.end());

        vector<int> inx2val(n);
        for (int i=0; i<n; ++i) 
            inx2val[i] = ranges::lower_bound(uni_arr, nums[i]) - uni_arr.begin();

        vector<int> cnt(uni_arr.size() + 1); int max_cnt = 0, min_val = 0;
        auto add = [&] ( int x) {
            int c = ++cnt[inx2val[x]];
            if (c > max_cnt) {
                max_cnt = c; min_val = nums[x];
            } else if (c == max_cnt) {
                min_val = min(min_val, nums[x]);
            }
        };

        vector<int> ans(m, -1);
        int bs = ceil(n / sqrt(m * 2));

        struct Query {
            int bid, l, r, threshold, qid;
        };

        vector<Query> qs;
        for (int i=0; i<m; ++i) {
            auto & q = queries[i];
            int l = q[0], r = q[1] + 1, threshold = q[2]; // 左闭右开
            if (r - l > bs) {
                qs.emplace_back(l/ bs, l, r, threshold, i);
                continue;
            }
            for (int j=l; j<r; j++) {
                add(j);
            }
            if (max_cnt >= threshold) ans[i] = min_val;
            ranges::fill(cnt, 0); max_cnt = 0;
        }

        ranges::sort(qs, {}, [](auto & q) {return pair(q.bid, q.r);});

        // 莫队算法的关键步骤
        int r; 
        for (int i=0; i<qs.size(); ++i) {
            auto& q = qs[i];
            int l0 = (q.bid + 1) * bs;
            if (i == 0 || q.bid > qs[i-1].bid) {
                r = l0; ranges::fill(cnt, 0); max_cnt = 0;
            }
            for (; r < q.r; r++) add(r);
            int tmp_max_cnt = max_cnt, tmp_min_val = min_val;

            for (int j = q.l; j < l0; j++) add(j);

            if (max_cnt >= q.threshold) ans[q.qid] = min_val;

            max_cnt = tmp_max_cnt; min_val = tmp_min_val;
            for (int j=q.l; j<l0; j++) cnt[inx2val[j]] --;
        }

        return ans;
    }
    
};
