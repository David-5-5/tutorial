#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.4 堆 - 第 K 小/大
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        // 自行解答
        vector<vector<int>> ans;
        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
        set<pair<int, int>> vis;
        int n = nums1.size(), m = nums2.size();
        
        pq.emplace(nums1[0]+nums2[0], 0, 0);
        vis.insert({0,0});
        while (ans.size() < min(n*m, k)) {
            auto [_, u, v] = pq.top(); pq.pop();
            ans.push_back({nums1[u], nums2[v]});

            if (u+1<nums1.size() && !vis.count({u+1,v})) {
                pq.emplace(nums1[u+1]+nums2[v], u+1, v);
                vis.insert({u+1, v});
            }
            if (v+1<nums2.size() && !vis.count({u,v+1})) {
                pq.emplace(nums1[u]+nums2[v+1], u, v+1);
                vis.insert({u, v+1});
            }
        }
        return ans; 
    }

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
