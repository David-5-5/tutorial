#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countKthRoots(int l, int r, int k) {
        // 枚举
        if (k == 1) return r - l + 1;
        int ans = 0;
        for (int i=0; i<=r; i++){
            int p = (int) pow(i, k);
            if (p > r) break;
            if (p >= l) ans ++;
        }

        return ans;
    }
};