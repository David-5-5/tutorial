#include <bits/stdc++.h>
using namespace std;

// 一、前缀和 1.2 前缀和与哈希表
class Solution {
public:
    int maxBalancedSubarray(vector<int>& nums) {
        struct PairHash {
            size_t operator()(const pair<int, int>& p) const {
                // 分别计算两个指针的哈希值
                size_t hash1 = std::hash<int>()(p.first);
                size_t hash2 = std::hash<int>()(p.second);
                
                // 组合两个哈希值（避免碰撞的简单方式）
                return hash1 ^ (hash2 << 1);
            }
        };         
        unordered_map<pair<int, int>, int, PairHash> pres; int n = nums.size();

        int prex = 0, pre01 = 0, ans = 0; pres[{0,0}] = -1;

        for (int i=0; i<n; i++) {
            prex ^= nums[i];
            if ( nums[i]%2 ) pre01++;
            else pre01--;
            
            if (pres.count({prex, pre01})) ans = max(ans, i - pres[{prex, pre01}]);
            else pres[{prex, pre01}] = i;
        }
        return ans;

    }

    int maxBalancedSubarray(vector<int>& nums) {
        unordered_map<long long, int> pres; int n = nums.size();
        
        // -n <= pre01 <= n, 0 <= pre01 + n <=2 * n
        // 因此 pre01 + n 进行偏移，初始 mask = (0 << 32) + 0 + n = n
        int prex = 0, pre01 = 0, ans = 0; pres[n] = -1; 

        for (int i=0; i<n; i++) {
            prex ^= nums[i];
            if ( nums[i]%2) pre01 ++;
            else pre01--;
            
            long long mask = (1LL * prex << 32) + (n + pre01);
            if (pres.count(mask)) ans = max(ans, i - pres[mask]);
            else pres[mask] = i;
        }
        return ans;
        
    }    
};