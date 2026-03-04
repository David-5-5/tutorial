#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.4 从最左/最右开始贪心
class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        // 自行解答
        int ans = 0;
        int n = strs.size(), m = strs[0].length(); vector<string> s_strs(n, "");
        for (int i = 0; i<m; i++) {
            bool to_del = false; bool nn = false;   // need next
            for (int j=1; j<n; j++) {
                if (s_strs[j] + strs[j][i] < s_strs[j-1] + strs[j-1][i]) {
                    to_del = true; break;
                } else if (s_strs[j] + strs[j][i] == s_strs[j-1] + strs[j-1][i]) nn = true;
            }
            if (to_del) ans ++;
            else if (!nn) return ans; else for (int j=0; j<n; j++) s_strs[j].push_back(strs[j][i]);
        }

        return ans;  
    }

 
};