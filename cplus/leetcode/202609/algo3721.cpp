#include <bits/stdc++.h>
using namespace std;

class LazySegmentTree {
    using T = pair<int, int>; // min, max of segment
    using F = int;            // type of lazy tag
    // 懒标记初始值
    const F TODO_INIT = 0; // **根据题目修改**

    struct Node {
        T val;
        F todo;
    };

    int n;
    vector<Node> tree;

    // 合并两个 val
    T merge_val(const T& a, const T& b) const {
        return {min(a.first, b.first), max(a.second, b.second)};
    }

    // 合并两个懒标记
    F merge_todo(const F& a, const F& b) const {
        return a + b;
    }

    // 把懒标记作用到 node 子树（本例为区间加）
    void apply(int node, int l, int r, F todo) {
        Node& cur = tree[node];
        // 计算 tree[node] 区间的整体变化
        cur.val.first += todo; cur.val.second += todo;
        cur.todo = merge_todo(todo, cur.todo);
    }

    // 把当前节点的懒标记下传给左右儿子
    void spread(int node, int l, int r) {
        Node& cur = tree[node];
        F todo = cur.todo;
        if (todo == TODO_INIT) { // 没有需要下传的信息
            return;
        }
        int m = (l + r) >> 1;
        apply(node * 2, l, m, todo);
        apply(node * 2 + 1, m + 1, r, todo);
        cur.todo = TODO_INIT; // 下传完毕
    }

    // 合并左右儿子的 val 到当前节点的 val
    void maintain(int node) {
        tree[node].val = merge_val(tree[node * 2].val, tree[node * 2 + 1].val);
    }

    // 用 a 初始化线段树
    // 时间复杂度 O(n)
    void build(const vector<T>& a, int node, int l, int r) {
        Node& cur = tree[node];
        cur.todo = TODO_INIT;
        if (l == r) { // 叶子
            cur.val = a[l]; // 初始化叶节点的值
            return;
        }
        int m = (l + r) >> 1;
        build(a, node * 2, l, m); // 初始化左子树
        build(a, node * 2 + 1, m + 1, r); // 初始化右子树
        maintain(node);
    }

    void update(int node, int l, int r, int ql, int qr, F f) {
        if (ql <= l && r <= qr) { // 当前子树完全在 [ql, qr] 内
            apply(node, l, r, f);
            return;
        }
        spread(node, l, r);
        int m = (l + r) >> 1;
        if (ql <= m) { // 更新左子树
            update(node * 2, l, m, ql, qr, f);
        }
        if (qr > m) { // 更新右子树
            update(node * 2 + 1, m + 1, r, ql, qr, f);
        }
        maintain(node);
    }

    // query 变形
    int find_first(int node, int l, int r, int ql, int qr, int target) {
        if (l > qr || r < ql || target < tree[node].val.first || target > tree[node].val.second) { 
            return -1; // target 不在 node [min, max] 区间内
        }

        if (l == r) return l;
        spread(node, l, r);
        int m = (l + r) >> 1;
        int idx = find_first(node * 2, l, m, ql, qr, target);
        if (idx < 0) { // 左子树未找到，继续右子树查找
            idx = find_first(node * 2 + 1, m + 1, r, ql, qr, target);
        }
        return idx;
    }

public:
    // 线段树维护一个长为 n 的数组（下标从 0 到 n-1），元素初始值为 init_val
    LazySegmentTree(int n, T init_val = {0, 0}) : LazySegmentTree(vector<T>(n, init_val)) {}

    // 线段树维护数组 a
    LazySegmentTree(const vector<T>& a) : n(a.size()), tree(2 << bit_width(a.size() - 1)) {
        build(a, 1, 0, n - 1);
    }

    void update(int ql, int qr, F f) {
        update(1, 0, n - 1, ql, qr, f);
    }

    int find_first(int ql, int qr, int target) {
        return find_first(1, 0, n - 1, ql, qr, target);
    }
};

class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size(); LazySegmentTree t(n+1); unordered_map<int, int> last;

        int ans = 0, cur_sum = 0;
        for (int i=1; i<=n; i++) {
            auto & x = nums[i-1];
            int v = x % 2? 1: -1;
            
            auto it = last.find(x);
            if (it == last.end()) {
                cur_sum += v;
                t.update(i, n, v);
            } else {
                t.update(it->second, i-1, -v);
            }
            last[x] = i;
            
            int start = t.find_first(0, i-1-ans, cur_sum);  // i-1-ans,只查找使 ans 增大的下标
            if (start>=0) ans = i - start;  // 查找进行剪枝
        }

        return ans;
    }
};