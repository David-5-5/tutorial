#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.2 堆 - 进阶
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        // 自行解答
        vector<int> cnt(k), avail;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq; 
        for (int i=0; i<k; i++) avail.push_back(i); // 初始所有服务器都可用

        for (int i=0; i<arrival.size(); i++) {
            int cur = arrival[i];
            while (!pq.empty() && pq.top().first <= cur) {
                auto it = ranges::lower_bound(avail, pq.top().second);
                avail.insert(it, pq.top().second); pq.pop();
            }
            if (avail.empty()) continue;

            auto it = ranges::lower_bound(avail, i%k);
            if (it == avail.end()) it = avail.begin();
            cnt[*it] += 1;
            pq.emplace(cur + load[i], *it); avail.erase(it);

        }

        int mx_cnt = 0;
        vector<int> ans;
        for (int i=0; i<k; ++i) {
            if (cnt[i] == mx_cnt) ans.push_back(i);
            else if (cnt[i] > mx_cnt) {
                ans.clear(); mx_cnt = cnt[i]; ans.push_back(i);
            }
        }
        return ans;
    }


};