#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 构造题
class Solution {
public:
    vector<vector<int>> reconstructMatrix(int upper, int lower, vector<int>& colsum) {
        // 自行解答
        int n = colsum.size();
        vector<vector<int>> ans(2, vector<int>(n));
        
        for (int i=0; i<n; i++) {
            if (colsum[i] == 2)  {
                ans[0][i] = 1, upper --;
                ans[1][i] = 1, lower --;
            } else if (colsum[i] == 1) {
                if (upper > lower) 
                    ans[0][i] = 1, upper --;
                else ans[1][i] = 1, lower --;
            }
            // Removing the statement is better
            // if (upper < 0 || lower < 0) return {};
        }
        if(upper!=0 || lower!= 0) return {};
        return ans;
    }
};