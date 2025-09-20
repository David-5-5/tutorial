#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 1;
int lpf[N];

int init = [] {
    memset(lpf, 0, sizeof(lpf));

    for (int i = 2; i < N; ++i) {      
        if (lpf[i] == 0) { // 质数
            for (int j = i; j < N; j += i) {
                if (lpf[j] == 0) lpf[j] = i;   // 质数 x 的 lpf(x) == x
            }
        }
    }
    return 0;
}();

// 数学算法 - 数论 - 1.3 质因数分解
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int ans = 0, n = nums.size();
        for (int i=n-2; i>=0; --i) {
            while (nums[i] > nums[i+1]) {
                ans ++;
                if (nums[i] == lpf[nums[i]]) {
                    return -1; // 质数无法减少
                } else nums[i] = lpf[nums[i]];
            }
        }
        return ans;
    }

};