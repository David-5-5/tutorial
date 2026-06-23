#include <bits/stdc++.h>
using namespace std;

// 七、其他线性 DP - 7.1 一维 DP
class Solution {
public:
    int maximumEnergy(vector<int>& energy, int k) {
        int ans = INT_MIN, n = energy.size();

        for (int i=0; i<n; i++) {
            if (i+k>=n) ans = max(energy[i], ans);
            else energy[i+k] = max(energy[i+k], energy[i+k] + energy[i]);
        }

        return ans;
    }
};