#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 双序列双指针 - 4.1 双指针
class Solution {
public:
    int smallestDifference(vector<int>& a, vector<int>& b) {
        // 自行解答
        sort(a.begin(), a.end()); sort(b.begin(), b.end());

        long long ans = INT_MAX;
        int n = a.size(), m = b.size(), a_p = 0, b_p = 0;
        while (a_p < n && b_p < m) {
            ans = min(ans, abs(1LL * a[a_p] - 1LL* b[b_p]));

            if (a[a_p] < b[b_p]) a_p ++;
            else b_p ++;
        }
        
        return ans;
    }
};