#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长公共子序列（LCS）
class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int m = str1.size(), n = str2.size();

        vector<vector<int>> memo(m, vector<int>(n, INT_MAX));
        auto dfs = [&](this auto&& dfs, int i, int j) -> int {
            if (i == m) return n - j;
            if (j == n) return m - i;

            auto& res = memo[i][j];
            if (res != INT_MAX) return res;
            
            if (str1[i] == str2[j]) res = min(res, 1 + dfs(i+1, j+1));
            else res = min(res, 1 + min(dfs(i+1, j), dfs(i, j+1)));
            return res;
        };
        
        int res = dfs(0, 0);
        string ans = "";
        function<void(int,int)> print_ans = [&](int i, int j) { // 不支持多个auto function
            if(i == m) {for (int k=j; k<n; k++) ans += str2[k]; return;}
            if(j == n) {for (int k=i; k<m; k++) ans += str1[k]; return;}

            if (str1[i] == str2[j]) {
                ans += str1[i];
                print_ans(i+1, j+1);
            } else {
                if (dfs(i+1, j) < dfs(i, j+1)) {
                    ans += str1[i];
                    print_ans(i+1,j);
                } else {
                    ans += str2[j];
                     print_ans(i,j+1);
                }
            }
        };
        print_ans(0, 0);
        return ans;

    }

    string shortestCommonSupersequence2(string str1, string str2) {
        // 参考题解，爆内存
        int m = str1.size(), n = str2.size();

        vector<vector<string>> memo(m, vector<string>(n));
        auto dfs = [&](this auto&& dfs, int i, int j) -> string {
            if (i < 0) return str2.substr(0, j);
            if (j < 0) return str1.substr(0, i);

            auto& res = memo[i][j];
            if (!res.empty()) return res;
            
            if (str1[i] == str2[j]) res = str1[i] + dfs(i+1, j+1);
            else {
                string res1 = str1[i] + dfs(i+1, j);
                string res2 = str2[j] + dfs(i, j+1);
                if (res1.size() < res2.size())
                    res = res1;
                else res = res2;
            }
            return res;
        };

        return dfs(m-1,n-1);
    }    
};