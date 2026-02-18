#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> countBits(int n) {
        // 同 338 题
        vector<int> ans(n+1);
        for (int i = 1; i <= n; ++i) {
            ans[i] = ans[i-(i&(~i+1))] + 1; // lowbits
        }
        return ans;          
    }
};