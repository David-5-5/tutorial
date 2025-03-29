#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.1 枚举右，维护左
class Solution {
public:
    long long numberOfSubsequences(vector<int>& nums) {
        // 自行解答 O(n^3) 超时
        int n = nums.size();
        long ans = 0;
        unordered_map<int, int> pval;
        
        for (int q=2; q<n; ++q) {
            pval[nums[q-2]] ++;
            for (int r=q+2; r<n; ++r) {
                for (int s=r+2; s<n; ++s) {
                    if (nums[q] * nums[s] % nums[r] == 0 ){
                        int v = nums[q] * nums[s] / nums[r];
                        ans += pval[v];
                    }
                }
            }
        }

        return ans;    

    }

    
    long long numberOfSubsequences2(vector<int>& nums) {
        // 参考题解，nums[p] * nums[r] == nums[q] * nums[s]
        // nums[p]/nums[q] == nums[s] / nums[r]
        // 考虑到这个思路，但是实现的具体步骤没有想清楚
        int n = nums.size(), ans = 0;
        unordered_map<int, int> pval;
        
        for (int q=2; q<n; ++q) {
            pval[nums[q-2]] ++;
            for (int r=4; q+1<r && r<n; ++r) {
                for (int s=6; r+1<s && s<n; ++s) {
                    if (nums[q] * nums[s] % nums[r] == 0 ){
                        int v = nums[q] * nums[s] / nums[r];
                        ans += pval[v];
                    }
                }
            }
        }

        return ans;

    }    
};