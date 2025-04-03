#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.1 前缀和基础
class Solution {
public:
    vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries) {
        // 自行解答
        int n = candiesCount.size();

        vector<long> pres(n+1);
        for (int i=0; i<n; i++) pres[i+1] = pres[i] + candiesCount[i];

        vector<bool> ans;
        for (auto& q : queries) {
            // 关键是从第 0 天开始
            ans.push_back(q[1]+1 <= pres[q[0]+1] && (long)q[2]*(q[1]+1) > pres[q[0]]);
            // ans.push_back(q[1] < pres[q[0]+1] && (long)q[2]*(q[1]+1) > pres[q[0]]);
        }
        return ans;   
    }
};