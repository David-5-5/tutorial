#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.1 堆 - 基础
class Solution {
public:
    vector<long long> findMaxSum(vector<int>& nums1, vector<int>& nums2, int k) {
        // 自行解答 多个数组按照 nums1 排序模板
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

    vector<long long> findMaxSum2(vector<int>& nums1, vector<int>& nums2, int k) {
        // 参考题解 - 简化
        int n = nums1.size(), idx[n];
        iota(idx, idx+n, 0);
        sort(idx, idx + n, [&](int i, int j) {
            return nums1[i] < nums1[j];
        });

        vector<long long> ans(n);
        long sum = 0;
        priority_queue<int, vector<int>, greater<>> pq;    //存储最大的k个数

        for (int i=0; i<n; ++i) {
            int x = idx[i];
            ans[x] = i>0 && nums1[x] == nums1[idx[i-1]]?ans[idx[i-1]]:sum;

            sum += nums2[x];
            pq.emplace(nums2[x]);
            if (pq.size() > k) {
                sum += - pq.top();
                pq.pop(); ;
            }
        }

        return ans;
    } 

    vector<long long> findMaxSum3(vector<int>& nums1, vector<int>& nums2, int k) {
        // 参考题解 - 分组循环 - 通用
        int n = nums1.size(), idx[n];
        iota(idx, idx+n, 0);
        sort(idx, idx + n, [&](int i, int j) {
            return nums1[i] < nums1[j];
        });

        vector<long long> ans(n);
        long sum = 0;
        priority_queue<int, vector<int>, greater<>> pq;    //存储最大的k个数

        // 存在值相等情况，分组循环
        for (int i=0; i<n;) {
            int start = i;
            // 找到所有相同的 nums1[i], 这些数的答案是一样的
            while (i<n && nums1[idx[start]] == nums1[idx[i]]) {
                ans[idx[i]] = sum;
                i++;
            }
            for (int j=start; j<i; ++j) {
                sum += nums2[idx[j]];
                pq.emplace(nums2[idx[j]]);
                if (pq.size() > k) {
                    sum += - pq.top();
                    pq.pop(); ;
                }
            }
        }

        return ans;
    }    
};