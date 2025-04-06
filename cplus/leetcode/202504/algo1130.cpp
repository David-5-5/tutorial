#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  区间 DP
class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {\
        // 参考题解 - 动态规划 O(n^3)
        int n = arr.size();

        vector<vector<int>> dp(n, vector<int>(n, INT_MAX/4)), mval(n, vector<int>(n));
        for (int j=0; j<n; j++) {
            mval[j][j] = arr[j];
            dp[j][j] = 0;
            for (int i=j-1; i>=0; i--) {
                mval[i][j] = max(arr[i], mval[i+1][j]);
                for (int k=i; k<j; k++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + mval[i][k]*mval[k+1][j]);
                }
            }
        }
        return dp[0][n-1];
    }

    int mctFromLeafValues2(vector<int>& arr) {\
        // 参考题解 - 单调栈 O(n) !!!
        int ans = 0;
        stack<int> st;
        for (int v: arr) {
            while (!st.empty() && st.top() <= v) {
                int u = st.top();
                st.pop();
                if (st.empty() || st.top() > v) {
                    ans += u * v;
                } else {
                    ans += st.top() * u;
                }
            }
            st.push(v);
        }

        while (st.size() >= 2) {
            int v = st.top();
            st.pop();
            ans += v * st.top();
        }
        return ans;
        
    }    
};