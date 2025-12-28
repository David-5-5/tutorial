#include <bits/stdc++.h>
using namespace std;

// 杂项 - 7.3 曼哈顿距离
class Solution {
public:
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
        // 自行解答 - 分类讨论
        // 令 i < j 有如下 4 种情况：
        // arr1[j] > arr1[i]    arr2[j] > arr2[i]: arr1[j] + arr2[j] + j - (arr1[i] + arr2[i] + i)
        // arr1[j] > arr1[i]    arr2[j] < arr2[i]: arr1[j] - arr2[j] + j - (arr1[i] - arr2[i] + i)
        // arr1[j] < arr1[i]    arr2[j] > arr2[i]: arr2[j] - arr1[j] + j - (arr2[i] - arr1[i] + i)
        // arr1[j] < arr1[i]    arr2[j] < arr2[i]: -arr1[j] - arr2[j] + j - (-arr1[i] - arr2[i] + i)
        int mn1 = arr1[0] + arr2[0], mn2 = arr1[0] - arr2[0], mn3 = arr2[0] - arr1[0], mn4 = -arr1[0] - arr2[0];
        int ans = 0, n = arr1.size();

        for (int i=1; i<n; ++i) {
            ans = max(ans, arr1[i] + arr2[i] + i - mn1);
            ans = max(ans, arr1[i] - arr2[i] + i - mn2);
            ans = max(ans, arr2[i] - arr1[i] + i - mn3);
            ans = max(ans, - arr1[i] - arr2[i] + i - mn4);

            mn1 = min(mn1, arr1[i] + arr2[i] + i);
            mn2 = min(mn2, arr1[i] - arr2[i] + i);
            mn3 = min(mn3, arr2[i] - arr1[i] + i);
            mn4 = min(mn4, -arr1[i] - arr2[i] + i);
        }
        return ans;  
    }

    int maxAbsValExpr2(vector<int>& arr1, vector<int>& arr2) {
        // 根据 3102 思路优化，计算出最大最小值即可
        int mn1 = INT_MAX, mn2 = INT_MAX, mn3 = INT_MAX, mn4 = INT_MAX;
        int mx1 = INT_MIN, mx2 = INT_MIN, mx3 = INT_MIN, mx4 = INT_MIN, n = arr1.size();

        for (int i=0; i<n; ++i) {
            mn1 = min(mn1, arr1[i] + arr2[i] + i); mx1 = max(mx1, arr1[i] + arr2[i] + i);
            mn2 = min(mn2, arr1[i] - arr2[i] + i); mx2 = max(mx2, arr1[i] - arr2[i] + i);
            mn3 = min(mn3, arr2[i] - arr1[i] + i); mx3 = max(mx3, arr2[i] - arr1[i] + i);
            mn4 = min(mn4, -arr1[i] - arr2[i] + i); mx4 = max(mx4, -arr1[i] - arr2[i] + i);
        }
        return max({mx1-mn1, mx2-mn2, mx3-mn3, mx4 -mn4});
    }

};