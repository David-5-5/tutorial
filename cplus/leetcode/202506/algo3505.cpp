#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.7 堆 - 对顶堆（滑动窗口第 K 小/大）
class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        // 自行解答 
        int n = nums.size();
        multiset<int> left, right;
        
        long long lsum = 0, rsum = 0;
        vector<long long> ops(n-x+1);
        for (int i=0; i<x-1; ++i) {
            right.emplace(nums[i]); rsum += nums[i];
        }
        // 将 right 中元素一分为二
        while (right.size()-left.size()>1) {
            lsum += *right.begin(); rsum -= *right.begin();
            left.emplace(*right.begin()); 
            right.erase(right.begin());
        }
        for (int i=x-1; i<n; ++i) {
            // 进最后一个元素
            rsum += nums[i];
            right.emplace(nums[i]);
            if (right.size()-left.size()>1) {
                lsum += *right.begin(); rsum -= *right.begin();
                left.emplace(*right.begin());
                right.erase(right.begin());                
            } else if (*right.begin() < * left.rbegin()) {
                lsum += *right.begin(); rsum -= *right.begin();
                left.emplace(*right.begin());
                right.erase(right.begin());
                lsum -= *left.rbegin(); rsum += *left.rbegin();
                right.emplace(*left.rbegin());
                left.erase(prev(left.end()));
            }
            ops[i-x+1] = rsum - right.size() * (*right.begin()) + (*right.begin()) * left.size() - lsum;
            // 删除第一个元素
            if (right.find(nums[i-x+1])!=right.end()) {
                rsum -= nums[i-x+1]; right.erase(right.find(nums[i-x+1]));  
            }else {
                lsum -= nums[i-x+1];
                left.erase(left.find(nums[i-x+1]));
            } 
        }
        
        vector memo(n, vector<long long>(k+1, -1L));
        auto dfs = [&](this auto&& dfs, int i, int j)-> long long {

            if (j == 0) return 0;
            auto & res = memo[i][j];

            if (res != -1L) return res;
            if (n-i < j * x) return res = LLONG_MAX/2;
            res = ops[i] + dfs(i+x, j-1); // 选
            
            return res = min(res, dfs(i+1,j));
        };
        
        return dfs(0, k);   
    }

};