#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  状态机 DP - 基础
class Solution {
public:
    int maximumSum(vector<int>& arr) {
        // 自行解答，前后缀分解
        int n = arr.size();
        
        int mx = ranges::max(arr);
        if (mx<0) return mx;

        vector<int> pres(n+1, 0);
        for (int i=0; i<n; i++) pres[i+1] = pres[i] + arr[i];

        vector<int> suf_mx(n+1, INT_MIN/2);
        suf_mx[n] = pres[n];
        for (int i=n-1; i>=0; i--) suf_mx[i] = max(suf_mx[i+1], pres[i]);

        int pre_mn = pres[0];
        int ans = INT_MIN/2;
        for (int i=0; i<n; i++ ) {
            pre_mn = min(pre_mn, pres[i]);
            ans = max(ans, pres[i] - pre_mn + max(0, arr[i]) + suf_mx[i+1] - pres[i+1]);
        }

        return ans;

    }
};