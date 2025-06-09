#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.1 堆 - 基础
class Solution {
public:
    vector<long long> findMaxSum(vector<int>& nums1, vector<int>& nums2, int k) {
        // 多个数组按照 nums1 排序模板
        int n = nums1.size(), idx[n];
        iota(idx, idx+n, 0);
        sort(idx, idx + n, [&](int i, int j) {
            return nums1[i] < nums1[j];
        });

        
        vector<long long> ans(n);
        long sum = 0;
        priority_queue<int, vector<int>, greater<>> pq;    //存储最大的k个数
        vector<int> to_append;
        for (int i=1; i<n; ++i) {
            int x = idx[i-1], y = idx[i];
            to_append.push_back(x);
            if (nums1[x] < nums1[y]) {
                for (auto j : to_append) {
                    if (pq.size() < k) {
                        pq.emplace(nums2[j]);
                        sum += nums2[j];
                    } else {
                        if (pq.top() < nums2[j]) {
                            sum += nums2[j] - pq.top();
                            pq.pop(); pq.emplace(nums2[j]);
                        }
                    }
                }
                ans[y] = sum;
            }
        }

        return ans;  
    }
};