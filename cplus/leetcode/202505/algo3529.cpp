#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 2.1 一维差分（扫描线）
class Solution {
public:
    int countCells(vector<vector<char>>& grid, string pattern) {

        auto kmp = [](string str, string pat) -> vector<int> {
            int n = str.size(), m = pat.size();
            vector<int> p_pi(m);
            for (int i=1; i < m; i++) {
                int j = p_pi[i-1];
                while (j > 0 && pat[j]!=pat[i])
                    j = p_pi[j-1];
                if (pat[j] == pat[i])
                    p_pi[i] = j + 1;
                else p_pi[i] = j;
            }

            vector<int> ans;
            int j = 0;
            for (int i=0; i<n; i++) {
                while (j > 0 && str[i] != pat[j])
                    j = p_pi[j-1];
                if (str[i] == pat[j]) j++;
                if (j == m) ans.push_back(i-j+1), j = p_pi[j-1];
            }

            return ans;
        };        

        int n = grid.size(), m = grid[0].size(), k = pattern.size();
        string horn_s = "", vert_s = "";
        
        vector<int> horn_d(n*m), vert_d(n*m);

        for (auto& row:grid) for(auto& ch:row)
            horn_s += ch;
        
        for (int c=0; c<m; ++c) for(int r=0; r<n; ++r)
            vert_s += grid[r][c];

        vector<int> h_match = kmp(horn_s, pattern);
        for (auto& v:h_match) {
            horn_d[v] ++;
            if (v+k < m*n) horn_d[v+k] --;
        }

        vector<int> v_match = kmp(vert_s, pattern);
        for (auto& v:v_match) {
            vert_d[v] ++;
            if (v+k < m*n) vert_d[v+k] --;  // v+k+1 是错误的
        }

        for (int i=1; i<n*m; ++i) horn_d[i] += horn_d[i-1];
        for (int i=1; i<n*m; ++i) vert_d[i] += vert_d[i-1];

        int ans = 0;
        for(int r=0; r<n; ++r)for (int c=0; c<m; ++c)
            if (horn_d[r*m+c] && vert_d[c*n+r]) ans ++;

        return ans;
    };

};