#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minLights(vector<int>& lights) {
        int n = lights.size(); vector<int> diff(n);
        for (int i=0; i<n; i++) {
            if (lights[i]) {
                auto l = max(0, i - lights[i]), r = min(n, i+lights[i] + 1);
                diff[l] ++;
                if (r < n) diff[r] --;
            }
        }

        for (int i=1; i<n; i++) {
            diff[i] += diff[i-1];
        }

        int ans = 0; int p = 0;
        while (p < n) {
            if (diff[p] == 0) {
                ans ++; p += 3;
            } else p ++;
        }

        return ans;
        
    }
};