#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 定长滑动窗口 1.1 基础
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        // 自行解答
        int n = customers.size(); int ans = 0, sat = 0, unsat = 0;
        for (int i=0; i<n; ++i) if (grumpy[i] == 0) sat += customers[i];
        for (int i=0; i<minutes-1; ++i) if (grumpy[i] == 1) unsat += customers[i];

        for (int i=minutes-1; i<n; ++i) {
            if (grumpy[i] == 1) unsat += customers[i];
            ans = max(ans, sat + unsat);
            if (grumpy[i-minutes+1] == 1) unsat -= customers[i-minutes+1];
        }

        return ans;
    }
};