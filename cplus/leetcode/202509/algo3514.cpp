#include <bits/stdc++.h>
using namespace std;

// 位运算 - 其他
class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        // 暴力求解
        unordered_set<int> hash1, hash2;
        for (auto& x: nums) for (auto& y:nums) hash1.insert(x^y);
        for (auto& x: nums) for (auto it=hash1.begin();it!=hash1.end();++it) hash2.insert(x^*it);
        return hash2.size();
    }

    int uniqueXorTriplets2(vector<int>& nums) {
        // 暴力求解, 使用 vector 代替 unordered_set
        int u = 1 << bit_width((unsigned) ranges::max(nums));
        vector<int> hash1(u), hash2(u);
        for (auto& x: nums) for (auto& y: nums) hash1[x^y] = true;
        for (int i=0; i<u; ++i) if (hash1[i]) for (auto& x: nums) hash2[x^i]=true;
        return reduce(hash2.begin(), hash2.end());  
    }


    int uniqueXorTriplets3(vector<int>& nums) {
        // 暴力求解, 使用 vector 代替 unordered_set
        int n = nums.size();
        int u = 1 << bit_width((unsigned) ranges::max(nums));
        vector<bool> hash1(u), hash2(u);
        for (int i=0; i<n; ++i) for (int j=i; j<n; ++j) hash1[nums[i] ^ nums[j]] = true;
        for (int i=0; i<u; ++i) if (hash1[i]) for (auto& x: nums) hash2[x^i]=true;
        // return reduce(hash2.begin(), hash2.end());
        int ans = 0; for (auto h:hash2) if (h) ans ++; return ans;  // 更快
    }



};