#include <bits/stdc++.h>
using namespace std;

// 三、字符串贪心 - 3.1 字典序最小/最大
class Solution {
public:
    vector<int> lexSmallestNegatedPerm(int n, long long target) {
        long long sum = 1L * n * (n + 1) / 2;

        if (target > sum || target < -sum  || (sum + target) % 2) return {};
        long long y = (sum - target) / 2;
        
        set<int> perm; for (int i=1; i<=n; ++i) perm.insert(i);
        set<int> pref;
        int cur = n;
        while (y) {
            int mx = min(y, (long long)cur);
            perm.erase(mx); pref.insert(-mx);
            y -= mx; cur --; 
        }
        vector<int> ans(pref.begin(), pref.end());
        ans.insert(ans.end(), perm.begin(), perm.end());
        return ans;     
    }
};