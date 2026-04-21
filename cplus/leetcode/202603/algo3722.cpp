#include <bits/stdc++.h>
using namespace std;

// 字符串 - 四、字符串哈希
class Solution {
public:
    string lexSmallest(string s) {
        // 暴力枚举 O(n^2)
        int n = s.length(); string ans = s;
        for (int l = 1; l<=n; l++) {
            auto prefix = s.substr(0, l), suffix = s.substr(n-l);
            reverse(prefix.begin(), prefix.end()); 
            reverse(suffix.begin(), suffix.end());

            ans = min(ans, prefix + s.substr(l));
            ans = min(ans, s.substr(0, n-l) + suffix);
        }

        return ans;
    }

    string lexSmallest(string s) {
        // 字符串哈希 O(nlogn)
        
    }    
};