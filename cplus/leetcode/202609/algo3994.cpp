#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minAdjacentSwaps(vector<int>& nums, int a, int b) {
        // 邻位交换法的次数 等于逆序对次数
        const int mod = 1e9 + 7;
        long long  ans = 0, cnt1 = 0, cnt2 = 0;
        for (auto v: nums) {
            if (v < a) {
                ans += cnt1 + cnt2;
            } else if (v <= b) {
                ans += cnt2; cnt1 ++;
            } else cnt2 ++;
        }

        return ans % mod;
    }
};