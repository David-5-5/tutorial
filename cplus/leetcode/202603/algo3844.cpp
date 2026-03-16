#include <bits/stdc++.h>
using namespace std;

// 三、Manacher 算法（回文串）
class Solution {
public:
    int almostPalindromic(string s) {
        // 中心扩展法 O(N^2)
        int ans = 0, n = s.length();

        auto expand = [&](int l, int r) {
            while (l>=0 && r<n && s[l]==s[r]) {
                l--, r++;
            }
            ans = max(ans, r-l-1);
        };
        
        for (int i=0; i<2*n; i++) {
            int l = i / 2, r = (i+1)/2; // i 等于偶数 奇回文，奇数偶回文
            while (l>=0 && r<n && s[l]==s[r]) {
                l--, r++;
            }
            expand(l-1, r); expand(l, r+1);
            if (ans >= n) return n;
        }
        return ans;
    }
};

int main() {
    cout << Solution().almostPalindromic("aaaba");
}