#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.2 堆 - 进阶
class Solution {
public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        // 自行解答
        
        int n = nums1.size(), idx[n];
        iota(idx, idx+n, 0);
        sort(idx, idx + n, [&](int i, int j) {
            return nums2[i] > nums2[j];
        });
        priority_queue<int, vector<int>, greater<>> pq;

        long long ans = 0, sum = 0;
        for (int i=0; i<k-1; ++i) {
            int inx = idx[i];
            sum += nums1[inx];
            pq.emplace(nums1[inx]);
        }

        for (int i=k-1; i<n; ++i) {
            int inx = idx[i];
            sum += nums1[inx]; pq.push(nums1[inx]);
            ans = max(ans, sum * nums2[inx]);
            sum -= pq.top(); pq.pop(); 
        }
        return ans;
    }
};;