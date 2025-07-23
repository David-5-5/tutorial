#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 7.2  并查集 - 进阶
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
            fa[x] = y;    // 大的连接小的
        }
    }

    bool is_same(int x, int y) {
        return find(x) == find(y);
    }
};


class Solution {
public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        // 自行解答
        // 可以交换的下标使用并查集合并为连通块，source 和 target 相同下标的元素合并到 multiset 中
        // 计算source 和 target的 multiset 中元素的不同值
        int n = source.size();
        UnionFind uf(n);
        for (auto& allow: allowedSwaps) {
            int u = allow[0], v = allow[1];
            uf.merge(u, v);
        }
        // 练习了 multiset 的用法
        unordered_map<int, multiset<int>> src;
        unordered_map<int, multiset<int>> tar;
        for (int i=0; i<n; ++i) {
            src[uf.find(i)].insert(source[i]);
            tar[uf.find(i)].insert(target[i]);
        }
        int ans = 0;
        for (auto& [key, src_set]: src) {
            auto tar_set = tar[key];
            for (auto & v: tar_set) {
                auto it = src_set.find(v);      // 删除相同的值
                if (it != src_set.end()) src_set.erase(it);
            }
            ans += src_set.size();              // 留下来的就是无法匹配的数量
        }
        return ans;
    }
};