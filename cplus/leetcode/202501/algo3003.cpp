#include <bits/stdc++.h>
using namespace std;

// 周赛 379
class Solution {
public:
    int maxPartitionsAfterOperations(string s, int k) {
        // c++ 自定义记忆化搜索比 python 慢
        if (k == 26) return 1;
        unordered_map<long long, int> memo;

        function<int(int, int, bool)> dfs = [&](int i, int mask, bool changed) -> int {
            if (i == s.size()) return 1;

            long long argMask = (long long) i << 32 | mask << 1 | changed;
            // 两种写法
            // if (memo.count(argMask)) return memo[argMask];
            auto it = memo.find(argMask);
            if (it != memo.end()) return it->second;
            
            int res = 0;
            // don't change i 
            if (__builtin_popcount(mask | 1 << (s[i]-'a')) > k) 
                res = dfs(i+1, 1 << (s[i]-'a'), changed) + 1;
            else res = dfs(i+1, mask | 1 << (s[i]-'a'), changed);

            // change i
            if (!changed) {
                for (int ch=0; ch<26; ch++) {
                    if (__builtin_popcount(mask | 1 << ch) > k) 
                        res = max(res, dfs(i+1, 1 << ch, true) + 1);
                    else res = max(res, dfs(i+1, mask | 1 << ch, true));
                }
            }
            
            return memo[argMask] = res;
        };

        return dfs(0,0,false);    

    }

    int maxPartitionsAfterOperations2(string s, int k) {
        if (k == 26) return 1;
        int n = s.length();
        int suf[10001][2] = {0}; // suf[i] 包含 段数，当前段的集合(long states)
        suf[n][0] = 1, suf[n][1] = 0;

        for (int i=n-1; i>=0; i--) {
            int bit = s[i] - 'a';
            int newMask = suf[i+1][1] | 1 << bit;
            if (__builtin_popcount(newMask) > k) {
                suf[i][0] = suf[i+1][0] + 1;
                suf[i][1] = 1 << bit;
            } else {
                suf[i][0] = suf[i+1][0];
                suf[i][1] = newMask;
            }
        }
        int ans = 0;
        int pre[10001][2];
        pre[0][0] =1, pre[0][1] = 0;
        for (int i=0; i<n; i++) {
            int unionSize = pre[i][1] | suf[i+1][1];
            if (__builtin_popcount(unionSize) < k){
                ans = max(ans, pre[i][0] + suf[i+1][0] - 1);
            } else if (__builtin_popcount(unionSize) < 26 
                &&__builtin_popcount(pre[i][1]) == k 
                && __builtin_popcount(suf[i+1][1]) == k ) {
                ans = max(ans, pre[i][0] + suf[i+1][0] + 1);
            } else {
                ans = max(ans, pre[i][0] + suf[i+1][0]);
            }

            int bit = s[i] - 'a';
            int newMask = pre[i][1] | 1 << bit;
            if (__builtin_popcount(newMask) > k) {
                pre[i+1][0] = pre[i][0] + 1;
                pre[i+1][1] = 1 << bit;
            } else {
                pre[i+1][0] = pre[i][0];
                pre[i+1][1] = newMask;
            }
            
        }

        return ans;

    } 

    int maxPartitionsAfterOperations3(string s, int k) {
        // 前后缀分解
        if (k == 26) return 1;
        int n = s.length();
        int suf[10001][2] = {0}; // suf[i] 包含 段数，当前段的集合(long states)
        suf[n][0] = 1, suf[n][1] = 0;

        // 抽象出通用方法，用于前后缀分解
        auto update = [&](int* src, int * dest, int bit, int newMask) {
            if (__builtin_popcount(newMask) > k) {
                dest[0] = src[0] + 1;
                dest[1] = 1 << bit;
            } else {
                dest[0] = src[0];
                dest[1] = newMask;
            }
        };

        for (int i=n-1; i>=0; i--) {
            int bit = s[i] - 'a';
            int newMask = suf[i+1][1] | 1 << bit;
            update(suf[i+1],suf[i],bit, newMask);
        }
        int ans = 0;
        int pre[10001][2];
        pre[0][0] =1, pre[0][1] = 0;
        for (int i=0; i<n; i++) {
            int unionSize = pre[i][1] | suf[i+1][1];
            if (__builtin_popcount(unionSize) < k){
                ans = max(ans, pre[i][0] + suf[i+1][0] - 1);
            } else if (__builtin_popcount(unionSize) < 26 
                &&__builtin_popcount(pre[i][1]) == k 
                && __builtin_popcount(suf[i+1][1]) == k ) {
                ans = max(ans, pre[i][0] + suf[i+1][0] + 1);
            } else {
                ans = max(ans, pre[i][0] + suf[i+1][0]);
            }

            int bit = s[i] - 'a';
            int newMask = pre[i][1] | 1 << bit;
            update(pre[i],pre[i+1],bit, newMask);
            
        }

        return ans;
    }

};