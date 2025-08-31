#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.3 划分型回溯
class Solution {
public:
    bool splitString(string s) {
        // 自行解答 - 相比较于python，c++需要处理整数越界的问题。
        const long long MX = 1e10;  // s 长度为 20，最大的prev 为10个9

        auto dfs = [&](this auto&& dfs, int i, long long prev, bool sta) -> bool {
            if (i == s.length()) return sta;
            long long cur = 0;
            for (int j=i; j<s.length(); ++j) {
                cur = cur * 10 + (s[j] - '0');
                if (cur > MX) break;
                if (prev==-1 || cur+1 == prev) {     
                    // prev!=-1?true:false 需要至少分为两段
                    if (dfs(j+1, cur, prev!=-1?true:false)) return true;
                }
            }
            return false;
        };
        return dfs(0, -1, false);
 
    }
};