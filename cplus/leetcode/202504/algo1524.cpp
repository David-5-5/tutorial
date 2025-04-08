#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.2 前缀和与哈希表
class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        // 自行解答
        const int mod = 1e9 + 7;

        int cnt[2]={1, 0}, n = arr.size(), ans = 0;
        arr[0] = arr[0] & 1;
        for (int i=1; i<n; i++) arr[i] = (arr[i] & 1) ^ arr[i-1];

        for (auto& v: arr) {
            ans =  (ans + cnt[v ^ 1]) % mod;

            cnt[v] = (cnt[v] + 1) % mod;
        }

        return ans;
    }
};