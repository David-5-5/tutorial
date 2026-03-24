#include <bits/stdc++.h>
using namespace std;

// 三、Manacher 算法（回文串）
class Solution {
public:
    int longestPalindrome(string s, string t) {
        // 参考题解，优化代码，一次完成计算
        int n = s.length(), m = t.length();
        
        vector<int> mx_s(n+1), mx_t(m+1);
        vector dp(n+1, vector<int>(m+1));
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (s[i] == t[j]) dp[i+1][j] = dp[i][j+1] + 1;
                mx_t[j] = max(mx_t[j], dp[i+1][j]);
            }
            mx_s[i+1] = ranges::max(dp[i+1]);
        }
        int ans = ranges::max(mx_s) * 2;

        for (int i=0; i<n*2-1; i++) {
            auto l = i/2, r = (i+1) /2;
            while (l>=0 && r<n && s[l]==s[r]) {
                l--, r++;
            }
            ans = max(ans, r-l-1+mx_s[l+1]*2);
        }
        for (int i=0; i<m*2-1; i++) {
            auto l = i/2, r = (i+1) /2; 
            while (l>=0 && r<m && t[l]==t[r]) {
                l--, r++;
            }
            ans = max(ans, r-l-1+mx_t[r]*2);
        }

        return ans;
    }
};

int main() {
    string s = "rtk", t = "hrgpgt";
    cout << Solution().longestPalindrome(s, t);
}