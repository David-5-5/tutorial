#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.8 其他
class Solution {
public:
    int numberOfArrays(vector<int>& differences, int lower, int upper) {
        // 自行解答 同 3468
        int L = lower, R = upper; int n = differences.size();
        for (int i = 0; i<n; ++i) {
            int diff = differences[i];
            L = max(L+diff, lower);
            R = min(R+diff, upper);
            if (L > R) return 0;
        }

        return R - L + 1;        
    }
};