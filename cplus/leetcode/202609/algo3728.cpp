#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countStableSubarrays(vector<int>& capacity) {
        struct PairHash {
            size_t operator()(const pair<long long, long long>& p) const {
                // 分别计算两个指针的哈希值
                size_t hash1 = std::hash<long long>()(p.first);
                size_t hash2 = std::hash<long long>()(p.second);
                
                // 组合两个哈希值（避免碰撞的简单方式）
                return hash1 ^ (hash2 << 1);
            }
        };         
        unordered_map<pair<int, long long>, int, PairHash> cnt;

        long long pres = 0, ans = 0; int n = capacity.size();
        for (int i=0; i<n; i++) {
            ans += cnt[{capacity[i], pres-capacity[i]}];
            // 延迟一步添加到哈希表，保证数组长度大于等于3
            if (i) cnt[{capacity[i-1], pres}] ++;  
            pres += capacity[i]; 
        }
        
        return ans;      

    }
};