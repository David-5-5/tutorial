#include <bits/stdc++.h>
using namespace std;

// 同 373
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        // 参考题解 - 避免 vis 数组 - 相关技巧关注注释语句
        vector<vector<int>> ans;
        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
        int n = nums1.size(), m = nums2.size();

        for (int i=0; i<min(k, n); i++)
            pq.emplace(nums1[i]+nums2[0], i, 0);    // 将 nums1 所有的元素 + nums2[0]

        while (ans.size() < min(n*m, k)) {
            auto [_, u, v] = pq.top(); pq.pop();
            ans.push_back({nums1[u], nums2[v]});

            if (v+1<m) pq.emplace(nums1[u]+nums2[v+1], u, v+1); // 增加 nums2的下一个元素
        }
        return ans; 
    }
};
