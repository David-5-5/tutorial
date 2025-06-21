#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.1 堆 - 基础
class Solution {
public:
    int maximumProduct(vector<int>& nums, int k) {
        // 自行解答，堆 + 贪心（最小值+1）
        const int mod = 1e9 + 7;
        priority_queue<int, vector<int>, greater<>> pq(nums.begin(), nums.end());

        while (k) {
            k --;
            int val = pq.top();
            pq.pop(); pq.push(val + 1);
        }

        int ans = 1;
        while (!pq.empty()) {
            ans = (long)ans * pq.top() % mod;
            pq.pop();
        }

        return ans;  
    }
};