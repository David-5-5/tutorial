#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int divisibleGame(vector<int>& nums) {
        // using set
        const int mod = 1e9 + 7; set<int> divs;
        for (auto & v: nums) {
            if (v == 1) continue;
            divs.insert(v); int mx = sqrt(v);
            for (int i=2; i<=mx; i++) {
                if (v % i == 0) {
                    divs.insert(i); divs.insert(v / i);
                }
            }
        }

        if (divs.empty()) return mod - 2;

        int ans = 0; long long global_mx = 0;
        for (auto it=divs.begin(); it!=divs.end(); it++) {
            auto k = *it; long long local_mx = 0, cur = 0;
            for (auto & v: nums) {
                if (cur < 0) cur = 0;
                if (v % k) cur -= v;
                else cur += v;
                local_mx = max(local_mx, cur);
            }
            if (local_mx > global_mx) {
                global_mx = local_mx; ans = local_mx * k % mod;
            }
        }

        return ans;        
    }

    int divisibleGame2(vector<int>& nums) {
        // using vector
        const int mod = 1e9 + 7; auto mx = ranges::max(nums);
        vector<bool> divs(mx + 1);
        for (auto & v: nums) {
            if (v == 1) continue;
            divs[v] = true; int mx = sqrt(v);
            for (int i=2; i<=mx; i++) {
                if (v % i == 0) {
                    divs[i] = true; divs[v/i] = true;
                }
            }
        }

        vector<int> factor;
        for (int i=0; i<=mx; i++) if (divs[i]) factor.emplace_back(i);
        if (factor.empty()) return mod - 2;

        int ans = 0; long long global_mx = 0;
        for (auto &k: factor) {
            long long local_mx = 0, cur = 0;
            for (auto & v: nums) {
                if (cur < 0) cur = 0;
                if (v % k) cur -= v;
                else cur += v;
                local_mx = max(local_mx, cur);
            }
            if (local_mx > global_mx) {
                global_mx = local_mx; ans = local_mx * k % mod;
            }
        }

        return ans;   
    }    
};