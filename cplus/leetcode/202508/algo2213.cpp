#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 8.3 树状数组和线段树 - 线段树（无区间更新）
class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        // 参考题解，线段树的包含的元素没有想明白
        int n = s.length();
        // 参考 oi-wiki 线段树模板 本题连续字符的最大数
        vector<tuple<int, int, int>> tree(4 * n);   // 线段树空间, 值:前缀最长字符，区间最长字符，后缀最长字符
        auto update = [&] (this auto&& update, int l, int start, int end, int p) -> void {
            if (l == start and l == end) {
                tree[p] = {1, 1, 1};  // 本题用于区间求和 根据题意修改
                return;
            }
            int m = start + ((end - start) >> 1);

            if (l <= m)
                update(l, start, m, p*2+1);
            else
                update(l, m + 1, end, p*2+2);
            
            tree[p] = {get<0>(tree[p*2+1]), max(get<1>(tree[p*2+1]), get<1>(tree[p*2+2])), get<2>(tree[p*2+2])};
            if (s[m] == s[m+1]) {
                auto merge = get<2>(tree[p*2+1])+get<0>(tree[p*2+2]);
                auto maxL = max(merge, get<1>(tree[p]));
                auto preL = get<0>(tree[p]) < (m-start+1)?get<0>(tree[p]): merge;
                auto sufL = get<2>(tree[p]) < (end-m)?get<2>(tree[p]): merge;
                tree[p] = {preL, maxL, sufL};
            }  
        };
        // 参考 oi-wiki 
        for (int i=0; i<n; ++i) update(i, 0, n-1, 0);

        int m = queryIndices.size();
        vector<int> ans(m); 
        for (int i=0; i<m; ++i) {
            s[queryIndices[i]] = queryCharacters[i];
            update(queryIndices[i], 0, n-1, 0);
            ans[i] = get<1>(tree[0]);
        }
        
        return ans;
    }

    vector<int> longestRepeating2(string s, string queryCharacters, vector<int>& queryIndices) {
        // 参考题解 - 独立出 build 方法
        int n = s.length();
        // 参考 oi-wiki 线段树模板 本题连续字符的最大数
        vector<tuple<int, int, int>> tree(4 * n);   // 线段树空间, 值:前缀最长字符，区间最长字符，后缀最长字符
        auto maintain = [&] (int start, int end , int p) -> void {
            tree[p] = {get<0>(tree[p*2+1]), max(get<1>(tree[p*2+1]), get<1>(tree[p*2+2])), get<2>(tree[p*2+2])};
            auto m = (start + end) / 2;
            if (s[m] == s[m+1]) {
                auto merge = get<2>(tree[p*2+1])+get<0>(tree[p*2+2]);
                auto maxL = max(merge, get<1>(tree[p]));
                auto preL = get<0>(tree[p]) < (m-start+1)?get<0>(tree[p]): merge;
                auto sufL = get<2>(tree[p]) < (end-m)?get<2>(tree[p]): merge;
                tree[p] = {preL, maxL, sufL};
            }  
        };

        auto build = [&] (this auto&& build, int start, int end, int p) -> void {
            if (start == end) {
                tree[p] = {1, 1, 1};  // 本题用于区间求和 根据题意修改
                return;
            }
            int m = start + ((end - start) >> 1);

            build(start, m, p*2+1);
            build(m + 1, end, p*2+2);
            maintain(start, end,  p);
        };
        

        auto update = [&] (this auto&& update, int l, int start, int end, int p) -> void {
            if (l == start and l == end) {
                tree[p] = {1, 1, 1};  // 本题用于区间求和 根据题意修改
                return;
            }
            int m = start + ((end - start) >> 1);

            if (l <= m)
                update(l, start, m, p*2+1);
            else
                update(l, m + 1, end, p*2+2);
            maintain(start, end,  p);
        };
        // 参考 oi-wiki 
        build(0, n-1, 0);

        int m = queryIndices.size();
        vector<int> ans(m); 
        for (int i=0; i<m; ++i) {
            s[queryIndices[i]] = queryCharacters[i];
            update(queryIndices[i], 0, n-1, 0);
            ans[i] = get<1>(tree[0]);
        }
        
        return ans;
    }
};