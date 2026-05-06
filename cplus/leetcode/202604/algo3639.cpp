#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.4 逆向思维
class Solution {
public:
    int minTime(string s, vector<int>& order, int k) {
        int n = s.length();
        vector<int> left, right; left.push_back(-1); right.push_back(n);
        
        
        if (k > 1LL * n * (n + 1) / 2) return -1;
        long long tot = 0;
        for (int i=0; i<n; i++) {
            auto l = ranges::upper_bound(left, order[i]) - left.begin() - 1;
            auto r = ranges::upper_bound(right, order[i]) - right.begin();
            tot += 1LL * (order[i] - left[l]) * (right[r]-order[i]);
            if (tot >= k) return i;
            left.insert(left.begin() + l+1, order[i]); right.insert(right.begin() + r, order[i]);
        }
        return 0; 
    }
};