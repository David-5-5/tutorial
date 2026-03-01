#include <bits/stdc++.h>
using namespace std;

// LCR series
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 自行解答，哈希 + 优先队列
        unordered_map<int, int> cnt;
        priority_queue<pair<int, int>> pq;
        
        for (auto v: nums) cnt[v] ++;

        for (auto &[k, v]: cnt) pq.emplace(v, k);

        vector<int> ans;
        for (int _=0; _<k; ++_) {
            ans.emplace_back(pq.top().second); pq.pop();
        }
        return ans;
    }
};