#include <bits/stdc++.h>
using namespace std;

// 同 421
class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        // 位运算 - 试填法 复习 2026.2.25
        int ans = 0;
        for (int i=30; i>=0; --i) {
            ans <<= 1; auto target = ans | 1;
            set<int> seen;
            for (auto v: nums) {
                int mask = (v >> i) ^ target;
                if (seen.count(mask)) {
                    ans = target; break;
                }
                seen.insert(v >> i);
            }

        }
        return ans;
    }    
};