#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 前后缀分解
class Solution {
public:
    vector<int> goodDaysToRobBank(vector<int>& security, int time) {
        // 自行解答
        int n = security.size();
        vector<int> suf(n);
        for (int i=n-2; i>=0; --i) {
            if (security[i] <= security[i+1]) suf[i] = suf[i+1] + 1;
            else suf[i] = 0;
        }

        int pre = 0; vector<int> ans;
        for (int i=0; i<n; ++i) {
            if (i && security[i-1] >= security[i]) pre += 1;
            else pre = 0;
            if (pre>=time && suf[i]>=time) ans.push_back(i);
        }
        return ans;
        
    }
};