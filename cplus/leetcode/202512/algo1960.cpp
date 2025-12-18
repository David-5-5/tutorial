#include <bits/stdc++.h>
using namespace std;

// Manacher 算法（回文串）
class Solution {
public:
    long long maxProduct(string s) {
        // 自行解答   2691 的难度，给自己点个赞
        int n = s.length();
        // BEGIN Manacher 马拉车 模板 仅奇数
        vector<int> d1(n);
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
            while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
                k++;
            }
            d1[i] = k--;
            if (i + k > r) {
                l = i - k;
                r = i + k;
            }
        }
        // END manacher 模板
        vector<int> suf_max(n); suf_max[n-1] = 1;
        for (int i=n-2, l=i; i>=0; --i) {
            for (int _; i-l<d1[i]; --l) {
                suf_max[l] = max(suf_max[l], 2 * (i-l) + 1);
            }
            suf_max[i] = max(suf_max[i], suf_max[i+1]);
        }
        vector<int> pre_max(n); pre_max[0] = 1;
        long long ans = 1 * suf_max[1];
        for (int i=1, r=i; i<n-1; i++) {
            for (int _; r-i <d1[i]; ++r) {
                pre_max[r] = max(pre_max[r], 2 * (r-i) + 1);
            }
            pre_max[i] = max(pre_max[i], pre_max[i-1]);
            ans = max(ans, 1LL * pre_max[i] * suf_max[i+1]);
        }
        return ans;
    }
};