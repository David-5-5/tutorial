#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 7.1 并查集 - 基础
class UnionFind {                   // 并查集模板
    vector<int> fa;
public:
    UnionFind(int n): fa(n) {
        ranges::iota(fa, 0);
    }

    int find(int x) {
        if (fa[x] != x) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }

    void merge(int from, int to) {
        int x = find(from), y = find(to);
        if (x != y) {
            fa[x] = y;
        }
    }

    bool is_same(int x, int y) {
        return find(x) == find(y);
    }
};

class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // 自行解答，使用 UnionFind 模板
        auto uf = UnionFind(n);

        for (int i=1; i<n; ++i) if (nums[i]-nums[i-1]<=maxDiff) uf.merge(i-1, i);

        vector<bool> ans;
        for (auto& q: queries) {
            int x = q[0], y = q[1]; ans.push_back(uf.is_same(x, y));
        }
        return ans;
    }

    vector<bool> pathExistenceQueries2(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // 参考题解，简化版并查集
        vector<int> idx(n);

        for (int i=1; i<n; ++i) idx[i] = idx[i-1] + (nums[i]-nums[i-1]>maxDiff);

        vector<bool> ans;
        for (auto& q: queries) {
            int x = q[0], y = q[1]; ans.push_back(idx[x] == idx[y]);
        }
        return ans;
    }

    vector<bool> pathExistenceQueries2(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // 参考题解，简化版并查集
        vector<int> idx;

        for (int i=1; i<n; ++i) if (nums[i]-nums[i-1]>maxDiff)
            idx.push_back(i-1);    //断点, 需要记在i-1上

        vector<bool> ans;
        for (auto q: queries) {
            ans.push_back(ranges::lower_bound(idx, q[0]) == ranges::lower_bound(idx, q[1]));
        }
        return ans;
    }    
};