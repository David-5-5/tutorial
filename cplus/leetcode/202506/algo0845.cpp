#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 前后缀分解
class Solution {
public:
    int longestMountain(vector<int>& arr) {
        // 自行解答
        int n = arr.size();
        vector<int> suf(n);
        for (int i=n-2; i>=0; --i) {
            if (arr[i] > arr[i+1]) suf[i] = suf[i+1] + 1;
        }

        int prefix = 0, ans = 0;
        for (int i=1; i<n-1; ++i) {
            if (arr[i]>arr[i-1]) prefix += 1;
            else prefix = 0;
            if (prefix && suf[i]) ans = max(ans, 1 + prefix + suf[i]);
        }

        return ans;
    }
};