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

};