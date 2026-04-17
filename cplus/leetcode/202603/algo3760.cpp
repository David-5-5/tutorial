#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.2 脑筋急转弯
class Solution {
public:
    int maxDistinct(string s) {
        vector<int> seen(26); int ans = 0;
        for (auto & ch: s) if (seen[ch-'a'] == 0) {
            ans ++; seen[ch-'a'] = 1;
        }

        return ans;
    }
};