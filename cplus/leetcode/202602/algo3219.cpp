#include <bits/stdc++.h>
using namespace std;

// 图论算法 四、最小生成树
// 贪心
class Solution {
public:
    long long minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        // 参考题解，贪心，按照切开销从大到小切，与 m, n 的数量无关
        int h_cuts = 0, v_cuts = 0;   // h_cuts 表示水平已经切的刀数， v_cuts 表示竖直已经切的刀数

        priority_queue<pair<int, int>> pq;    // 大根堆
        for (auto & h : horizontalCut ) {
            pq.emplace(h, 0);
        }
        for (auto & v : verticalCut ) {
            pq.emplace(v, 1);
        }
        long long ans = 0;
        while (!pq.empty()) {
            auto [c, d] = pq.top(); pq.pop();
            if (d == 0) {
                ans += c * (v_cuts + 1); h_cuts ++;
            } else {
                ans += c * (h_cuts + 1); v_cuts ++;
            }
        }
        return ans;  
    }


};