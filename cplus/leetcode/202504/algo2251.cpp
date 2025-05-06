#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 2.1 一维差分（扫描线）
class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        unordered_map<int, int> diff_m;

        for (auto& f: flowers) {
            int start = f[0], end = f[1]+1;
            diff_m.count(start)? diff_m[start] += 1: diff_m[start] = 1;
            diff_m.count(end)? diff_m[end] -= 1: diff_m[end] = -1;
        }

        vector<pair<int, int>> diff_v;
        for (auto& [i, c]: diff_m) diff_v.push_back({i, c});
        sort(diff_v.begin(), diff_v.end());


        int n = people.size(); 
        vector<int> ans(n), ids;
        for (int i=0; i<n; ++i) ids.push_back(i);

        sort(ids.begin(), ids.end(), [&](int a, int b){
            return people[a] < people[b];
        });
        // sort(people.begin(), people.end());

        int l1 = 0, cnt = 0;
        for (int l2=0; l2<n; ++l2) {
            while (l1 < diff_v.size() && diff_v[l1].first <= people[ids[l2]]) {
                cnt += diff_v[l1++].second;
            }
            ans[ids[l2]] = cnt;
        }

        return ans;     

    }
};