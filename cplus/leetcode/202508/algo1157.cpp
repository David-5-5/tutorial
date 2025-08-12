#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 8.3 树状数组和线段树 - 线段树（无区间更新）
class MajorityChecker {
private:
    vector<int> arr;
    vector<unordered_map<int, int>> tree;
    unordered_map<int, int> cnt;
public:
    MajorityChecker(vector<int>& arr): tree(4*arr.size()) {
        // 自行解答
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


/**
 * Your MajorityChecker object will be instantiated and called as such:
 * MajorityChecker* obj = new MajorityChecker(arr);
 * int param_1 = obj->query(left,right,threshold);
 */