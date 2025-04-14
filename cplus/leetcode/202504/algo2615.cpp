#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.3 距离和
class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        // 自行解答 绝对值之和 同 1685
        int n = nums.size();
        unordered_map<int, vector<int>> groups;

        for (int i=0; i<n; i++) groups[nums[i]].push_back(i);

        vector<long long> ans(n);
        
        for (auto& [_, v]: groups) {
            int m = v.size();
            if (m == 1) continue;

            vector<long long> pres(m+1);
            for (int i=0; i<m; i++) pres[i+1] = pres[i] + v[i];

            for (int i=0; i<m; i++) 
                ans[v[i]] = pres[m] + (long)v[i] *(2*i+1-m)-pres[i]-pres[i+1];
        }

        return ans; 
    }
};