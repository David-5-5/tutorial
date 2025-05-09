#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 2.1 一维差分（扫描线）
class Solution {
public:
    int countCells(vector<vector<char>>& grid, string pattern) {
        // 自行解答 差分数组 + KMP
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

        // 按行生成字符串
        for (auto& row:grid) for(auto& ch:row)
            horn_s += ch;
        
        // 按列生成字符串
        for (int c=0; c<m; ++c) for(int r=0; r<n; ++r)
            vert_s += grid[r][c];

        // 统计匹配的水平字符串
        vector<int> h_match = kmp(horn_s, pattern);
        for (auto& v:h_match) {         // 每个匹配的子串的单元格 +1, 用差分优化
            horn_d[v] ++;
            if (v+k < m*n) horn_d[v+k] --;
        }

        // 统计匹配的垂直字符串
        vector<int> v_match = kmp(vert_s, pattern);
        for (auto& v:v_match) {
            vert_d[v] ++;
            if (v+k < m*n) vert_d[v+k] --;  // v+k+1 是错误的
        }

        // 计算前缀和，即按行按列每个单元格匹配的次数
        for (int i=1; i<n*m; ++i) horn_d[i] += horn_d[i-1];
        for (int i=1; i<n*m; ++i) vert_d[i] += vert_d[i-1];

        int ans = 0;
        for(int r=0; r<n; ++r)for (int c=0; c<m; ++c)
            // 同一单元格再水平和垂直的差分位置不同
            // 次数都大于 1，计数 + 1
            if (horn_d[r*m+c] && vert_d[c*n+r]) ans ++;

        return ans;
    };

};