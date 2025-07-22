#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 7.2  并查集 - 进阶
class UnionFind {
    vector<int> fa;
public:
    int cc;         // 连通块个数
    UnionFind(int n): fa(n), cc(n) {
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
            fa[x] = y; cc--;
        }
    }
};


class Solution {
public:
    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
        // 参考题解 - 带限制的连通图
        UnionFind uf(n);
        vector<bool> ans(requests.size());
        for (int i = 0; i < requests.size(); ++i) {
            auto& r = requests[i];
            int a = uf.find(r[0]), b = uf.find(r[1]);
            bool check = true;
            for (auto& rest : restrictions) {   // rest[0] 和 rest[1] 不能连通
                int c = uf.find(rest[0]), d = uf.find(rest[1]);
                // r[0] 与 rest[0] 同组，r[1] 与 rest[1] 同组
                // 或 r[0] 与 rest[1] 同组，r[1] 与 rest[0] 同组 两种情况会导致限制连通，
                // 因此 r[0] r[1] 不能合并
                if ((a == c && b == d)|| (a == d && b == c)) {
                    check = false; break;
                }
            }
            if (check) uf.merge(r[0], r[1]);
            ans[i] = check;

        }
        return ans;
    }
};