#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.1 从最小/最大开始贪心
class Solution {
public:
    long long maxPoints(vector<int>& technique1, vector<int>& technique2, int k) {
        // 自行解答 按照 technique1[i] - technique2[i] 倒序排列
        int n = technique1.size(), idx[n];
        iota(idx, idx+n, 0);
        sort(idx, idx + n, [&](int i, int j) {
            return technique1[i]-technique2[i] > technique1[j]-technique2[j];
        });
        long long ans = 0;
        for (int i=0; i<n; ++i) {
            auto id = idx[i];
            if (i < k) ans += technique1[id];
            else ans += max(technique1[id], technique2[id]);
        }

        return ans;
    }
};