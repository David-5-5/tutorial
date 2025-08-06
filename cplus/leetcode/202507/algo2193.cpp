#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 8.2 树状数组和线段树 - 逆序对
template<typename T>
class FenwickTree {
    vector<T> tree;

public:
    // 使用下标 1 到 n
    FenwickTree(int n) : tree(n + 1) {}
    // a[i] 增加 val, 1 <= i <= n
    void update(int i, T val) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }
    // 求前缀和 a[1] + ... + a[i] 1 <= i <= n
    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) { // i-= i&-i
            res += tree[i];
        }
        return res;
    }
    // 求区间和 a[l] + ... + a[r], 1 <= l <= r <= n
    T query(int l, int r) const {
        if (r < l) {
            return 0;
        }
        return pre(r) - pre(l - 1);
    }
};

class Solution {
public:
    int minMovesToMakePalindrome(string s) {
        // 参考题解 复习
        unordered_map<char, int> freq;
        for (auto ch: s) freq[ch] ++;

        int ans = 0, lcnt = 0, rcnt = 0, n = s.length();
        unordered_map<char, vector<int>> left, right;
        for (int i=0; i < n; ++i) { // 将 s 分前后两部分，保持原有的字符的顺序不变，需要由 0 开始
            auto ch = s[i];
            if (left[ch].size() + 1 <= freq[ch]/2) {
                left[ch].push_back(lcnt++);
                ans += i - lcnt + 1;    // left 字符的序号和 - sum(0, 1, ..,lcnt-1)
            } else right[ch].push_back(rcnt++);
        }

        if (n % 2) {    // 长度为奇数
            for (auto& [ch, cnt]: freq) {   // 补齐
                if (cnt % 2) {
                    left[ch].push_back(lcnt++);
                    break;
                }
            }
        }

        vector<int> perm((n+1)/2);
        for (auto &[ch, seq]: right) {
            for (int i=0; i<seq.size(); i++) {
                // 左边的字符下标 设置 到对应右边的字符, 多个相同字符按中心对称
                // 左边字符为 a a b c d，下标顺序为0, 1, 2, 3, 4
                // 右边字符为 b a c a d, 右边字符的下标为 2, 1, 3, 0, 4，
                // 其中a有多个，右边按照左边的倒序顺序编码下标
                perm[seq[i]] = left[ch][seq.size()-1-i];    
            }
        }

        // 求顺序对，（回文的倒序，求逆序转化为求正序）
        FenwickTree<int> ft(n);
        for (auto r: perm) {
            ans += ft.pre(r);
            ft.update(r+1, 1);
        }

        return ans;
    }
};