#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.1 堆 - 基础
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        // 堆 + 分组循环
        int n = tasks.size();
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq_wrk_srvs;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq_avb_srvs;
        vector<int> ans(n);
        for (int i=0; i<servers.size(); ++i) pq_avb_srvs.emplace(servers[i], i);

        int start = 0;
        for (int i=0; i<n; ) {
            if (pq_avb_srvs.size()==0) {
                start = pq_wrk_srvs.top().first;
            }
            while (pq_wrk_srvs.size() && pq_wrk_srvs.top().first<=start) {
                int srv_id = pq_wrk_srvs.top().second;
                pq_avb_srvs.emplace(servers[srv_id], srv_id);
                pq_wrk_srvs.pop();
            }
            while (pq_avb_srvs.size() && i<=start && i<n) {
                int srv_id = pq_avb_srvs.top().second;
                pq_avb_srvs.pop();
                pq_wrk_srvs.emplace(start+tasks[i], srv_id);
                ans[i++] = srv_id;
            }
            start++;
        }
        
        return ans;

    }
};