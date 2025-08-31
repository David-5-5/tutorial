#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.2 子集型回溯
class Solution {
public:
    int maximumGood(vector<vector<int>>& statements) {
        // 自行解答
        int n = statements.size();
        int mx_count = 0;
        for (int mask=(1<<n)-1; mask; --mask) {
            bool correct = true;
            for (int i=0; i<n; ++i) {
                if (((mask>>i)&1) == 0) continue;
                for (int j=0;j<n && correct;++j) {
                    if (statements[i][j] == 2) continue;
                    if (statements[i][j] != ((mask>>j)&1)) {
                        correct = false; break;
                    }
                }
            }
            if (correct) mx_count = max(mx_count, __builtin_popcount(mask));
        }

        return mx_count;
    }


};