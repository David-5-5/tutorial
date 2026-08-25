#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
int memo[MAXN][26][26];

class Solution {
public:
    int minimizeConcatenatedLength(vector<string>& words) {
int n = words.size();
        memset(memo, -1, sizeof(memo));

        function<int(int, char, char)> dfs = [&](int i, char h, char t) -> int {
            if (i == n) return 0;
            int hi = h - 'a', ti = t - 'a';
            if (memo[i][hi][ti] != -1) return memo[i][hi][ti];

            const string& s = words[i];
            int sz = s.size();
            int op1 = sz + dfs(i+1, h, s.back()) - (t == s[0] ? 1 : 0);
            int op2 = sz + dfs(i+1, s[0], t) - (h == s.back() ? 1 : 0);
            return memo[i][hi][ti] = min(op1, op2);
        };

        return words[0].size() + dfs(1, words[0][0], words[0].back());   
    }
};