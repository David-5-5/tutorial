#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        // 自行解答 Rabin Karp + 二分
        const int base = 113, mod = 1e9 + 7;
        int n = nums.size();
        
        auto check = [&](int len) -> bool {
            if (len == 0) return true;

            long long hash = 0, blen = 1;
            for (int i=0; i<len-1; i++) {
                hash = (hash * base + nums[i]) % mod;
                blen = blen * base % mod;
            }
            unordered_map<int, int> freqs;
            hash = (hash * base + nums[len-1]) % mod;
            freqs[hash] ++;
            
            for (int i=len; i<n; i++) {
                hash = ((mod + hash - nums[i-len] * blen % mod) * base + nums[i]) % mod;
                freqs[hash] ++;
            }

            return any_of(freqs.begin(), freqs.end(), [](auto & p) {
                return p.second == 1;
            });

        };
        
        int l = 0, r = n + 1;
        while (l + 1 < r) {
            auto mid = (l + r) / 2;
            (check(mid)?r:l) = mid;
        }

        return r;
    }
}; 