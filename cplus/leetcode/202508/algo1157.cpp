#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 8.3 树状数组和线段树 - 线段树（无区间更新
class MajorityChecker {
private:
    vector<int> arr;
    vector<unordered_map<int, int>> tree;
    unordered_map<int, int> cnt;
public:
    MajorityChecker(vector<int>& arr): tree(4*arr.size()) {
        // 自行解答 - 线段树
        int n = arr.size();
        this->arr = arr;
        for (auto& v: arr) {
            cnt[v]++;
        }
        build(0, n-1, 0);   
    }

    void build(int s, int t, int p) {
        if (s == t) {
            tree[p][arr[s]] = 1;
            return;
        }
        int m = (s + t) / 2;
        build(s, m, p*2+1);
        build(m+1, t, p*2+2);
        for (auto& [k,v]: tree[p*2+1]) {
            tree[p][k] += v;
        }
        for (auto& [k,v]: tree[p*2+2]) {
            tree[p][k] += v;
        }
        filter(tree[p], (t-s+1)/2+1);
    }

    void filter(unordered_map<int, int>& mp, int threshold) {
        auto it = mp.begin();
        while (it != mp.end()) {
            // 检查当前元素的值是否小于阈值
            if (cnt[it->first] < threshold) {
                // 删除当前元素，并获取下一个迭代器
                it = mp.erase(it);
            } else {
                // 移动到下一个元素
                ++it;
            }
        }
    }

    unordered_map<int, int> query(int l, int r, int threshold, int s, int t, int p) {
        if (l <= s && t <= r) return tree[p];
        
        int m = (s+t)/2;
        unordered_map<int, int> left, right;
        if (l<=m) left = query(l, r, threshold, s, m, p*2+1);
        if (r>m)  right = query(l, r, threshold, m+1, t, p*2+2);
        for (auto& [k, v]: right)left[k]+=v;
        filter(left, threshold);
        return left;
    }

    int query(int left, int right, int threshold) {
        
        int ans = -1, n = arr.size();
        auto res = query(left, right, threshold, 0, n-1, 0);
        for (auto&[k,v]:res) if (v>=threshold) ans = k;
        return ans;
    }
};


// 数学算法 - 随机算法 - 6.1 随机数
class MajorityChecker {
private:
    int k = 20;
    vector<int> arr;
    unordered_map<int, vector<int>> idx;
public:
    MajorityChecker(vector<int>& arr) {
        // 参考题解，随机化方法
        int n = arr.size();
        this->arr = arr;
        for (int i=0; i<n; ++i) {
            idx[arr[i]].emplace_back(i);
        }
    }

    int query(int left, int right, int threshold) {
        for (int _=0; _ < k; _++) {
            int offset = rand() % (right - left + 1);
            int x = arr[left+offset];
            int occ = ranges::lower_bound(idx[x], right+1) - ranges::lower_bound(idx[x], left);
            if (occ >= threshold) return x;
        }
        return -1;
    }
};

/**
 * Your MajorityChecker object will be instantiated and called as such:
 * MajorityChecker* obj = new MajorityChecker(arr);
 * int param_1 = obj->query(left,right,threshold);
 */