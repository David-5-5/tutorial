#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.1 枚举右，维护左
class Solution {
public:
    int countQuadruplets(vector<int>& nums) {
        unordered_map<int, int> cnt;
        int n = nums.size(), ans = 0;

        for (int i=2; i<n; ++i) cnt[nums[i]]++;

        for (int i=2; i<n; ++i) {
            cnt[nums[i]] --;
            for (int j=1; j<i; ++j) {
                for (int k=0; k<j; ++k) {
                    int v = nums[i]+nums[j]+nums[k];
                    ans += cnt[v];
                }
            }
        }
        return ans;  
    }



};