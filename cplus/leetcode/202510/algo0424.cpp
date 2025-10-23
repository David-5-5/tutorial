#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 求子数组个数 2.4 其他（选做）
class Solution {
public:
    int characterReplacement(string s, int k) {
        // 自行解答，差一点
        int ans = 0, l = 0, n = s.length(), maxn = 0;
        unordered_map<char, int> cnt;
        for (int r = 0; r<n; ++r) {
            cnt[s[r]] ++;
            maxn = max(maxn, cnt[s[r]]); // 始终找窗口中出现频率最大的值
            while (r-l+1 - maxn > k) {
                cnt[s[l]] --;
                l ++;
            }
            if (r-l+1-maxn == k) ans = max(ans, r-l+1);
            else ans = max(ans, r-l+1 + min(k+maxn+l-r-1, n-r-1)); // 修改后面
        }
        return ans;     
    }

    int characterReplacement2(string s, int k) {
        // 自行解答，差一点
        int ans = 0, l = 0, n = s.length(), maxn = 0;
        vector<int> freqs;
        for (int r = 0; r<n; ++r) {
            freqs[s[r]-'A'] ++;
            maxn = max(maxn, freqs[s[r]-'A']); // 始终找窗口中出现频率最大的值
            while (r-l+1 - maxn > k) {
                freqs[s[l]-'A'] --;
                l ++;
            }
            if (r-l+1-maxn == k) ans = max(ans, r-l+1);
            else ans = max(ans, r-l+1 + min(k+maxn+l-r-1, n-r-1)); // 修改后面
        }
        return ans;     
    }    
};