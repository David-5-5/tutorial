#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.1 堆 - 基础
class Solution {
public:
    int minStoneSum(vector<int>& piles, int k) {
        // 自行解答，初始化
        priority_queue<int, vector<int>, less<>> pq(piles.begin(), piles.end());

        for (int _=0; _<k; ++_) {
            int val = pq.top();
            pq.pop();
            pq.push((val+1)/2);
        }

        int ans = 0;
        while (!pq.empty()) {
            ans += pq.top();
            pq.pop();
        }
        return ans;
    }
};