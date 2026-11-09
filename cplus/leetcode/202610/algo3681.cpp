#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxXorSubsequences(vector<int>& nums) {
        // 参考题解，线性基
        int len = 30;
        vector<int> p(len);

        for (auto & x: nums)  for (int i=len-1; i>=0; i--) if (x >> i & 1) {
            if (p[i] == 0) {p[i] = x; break;}
            x ^= p[i];
        }
        
        int ans = 0;
        for (int i=len-1; i>=0; i--) ans = max(ans, ans ^ p[i]);
        return ans;
    }
};

