#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 定长滑动窗口 1.1 基础
class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        // 滑动窗口 自行解答
        int ans = 0, sum = 0;
        for (int i=0; i<k-1; i++) sum+= arr[i];

        for (int i=k-1; i<arr.size(); ++i) {
            sum += arr[i];
            if (sum/k >= threshold) ans ++;
            sum -= arr[i-k+1];
        }
        return ans;
    }
};