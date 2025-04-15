#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.4 前缀异或和
class Solution {
public:
    vector<bool> canMakePaliQueries(string s, vector<vector<int>>& queries) {
        // 自行解答
        int n = s.length();
        vector<int> prex(n+1);
        for (int i=0; i<n; i++) prex[i+1] = prex[i] ^ (1 << (s[i]-'a'));

        vector<bool> ans;
        for (auto q: queries) {
            int v = prex[q[1]+1] ^ prex[q[0]];
            if (__builtin_popcount(v)/2 <= q[2]) ans.push_back(true);
            else ans.push_back(false);
        }
        return ans;   
    }
};