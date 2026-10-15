#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        set<int> vis; set<pair<int, int>> kdiffs;
        for (auto v: nums) {
            if (vis.count(v-k)) kdiffs.emplace(v-k, v);
            if (vis.count(v+k)) kdiffs.emplace(v, v+k);
            vis.emplace(v);
        }

        return kdiffs.size();
    }

    int findPairs2(vector<int>& nums, int k) {
        // 简化，性能并未提升
        set<int> vis, kdiffs;
        for (auto v: nums) {
            if (vis.count(v-k)) kdiffs.emplace(v-k);
            if (vis.count(v+k)) kdiffs.emplace(v);
            vis.emplace(v);
        }

        return kdiffs.size();
    }    
};