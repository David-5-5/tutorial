#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.2 堆 - 进阶
class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        // 自行解答
        const int mod = 1e9 + 7;
        int idx[n];
        iota(idx, idx+n, 0);
        sort(idx, idx + n, [&](int i, int j) {
            return efficiency[i] > efficiency[j];
        });
        priority_queue<int, vector<int>, greater<>> pq;

        long long ans = 0, sum = 0;

        for (int i=0; i<n; ++i) {
            int inx = idx[i];
            sum += speed[inx]; pq.push(speed[inx]);
            ans = max(ans, sum * efficiency[inx]);
            if (pq.size() == k) {sum -= pq.top(); pq.pop(); }
        }
        return ans % mod;        
    }
};