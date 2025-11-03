#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.1 相向双指针
class Solution {
public:
    int threeSumMulti(vector<int>& arr, int target) {
        const int mod = 1e9 + 7; int ans = 0;
        vector<int> cnt(101);
        for (auto v:arr) cnt[v] ++;
        for (int m = 0; m<=100; m++) {
            if (cnt[m] == 0) continue;
            int l = 0, r = 100;
            while (l <= r) {
                while (cnt[l] == 0) l++;
                while (cnt[r] == 0) r--;
                if (l > m) break;
                if (r < m) break;
                if (l + r + m < target) l++;
                else if (l + r + m > target) r--;
                else { // l + r + m == target
                    if (l == m && m == r) {
                        ans = (ans + 1LL * cnt[m] * (cnt[m]-1) * (cnt[m]-2) / 6) % mod;
                    } else if (l == m) {
                        ans = (ans + 1LL * cnt[r] * cnt[m] * (cnt[m]-1) / 2 ) % mod;
                    } else if (r == m) {
                        ans = (ans + 1LL * cnt[l] * cnt[m] * (cnt[m]-1) / 2 ) % mod;
                    } else {
                        ans = (ans + cnt[l] * cnt[m] * cnt[r]) % mod;
                    }
                    l++, r--;
                }
            }
        }
        return ans;
    }
};