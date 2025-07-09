#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.6 堆 - 懒删除堆
class Solution {
public:
    vector<long long> mostFrequentIDs(vector<int>& nums, vector<int>& freq) {
        // 自行解答 - 懒删除堆
        priority_queue<pair<long long, int>> pq;
        unordered_map<int, long long> freqs;

        int n = nums.size();
        vector<long long> ans(n);
        for (int i = 0; i<n; ++i) {
            freqs[nums[i]] += freq[i];
            if (freqs[nums[i]]) pq.emplace(freqs[nums[i]], nums[i]);
            // 堆顶元素的 元素值-频率和 freqs不一致，为无效元素，从堆顶删除
            while (pq.size() && pq.top().first != freqs[pq.top().second]) pq.pop();

            if (pq.size()) ans[i] = pq.top().first;
        }

        return ans;
    }
};