#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 六、分组循环
class Solution {
public:
    int findSubstringInWraproundString(string s) {
        // 自行解答
        vector<int> cnt(26);

        int ans = 1, prev = 1, n = s.length();
        cnt[s[0]-'a'] = 1;
        for (int i=1; i<n; ++i) {
            if ((s[i-1]-'a' + 1)%26 == s[i]-'a')
                prev += 1;
            else prev = 1;

            if (cnt[s[i]-'a'] < prev) {
                ans += prev - cnt[s[i]-'a'];
                cnt[s[i]-'a'] = prev;
            }
        }
        return ans;        
    }

        int findSubstringInWraproundString(string s) {
        // 参考题解的写法 - 代码精简
        vector<int> cnt(26);

        int prev = 1, n = s.length();
        cnt[s[0]-'a'] = 1;
        for (int i=1; i<n; ++i) {
            if ((s[i-1]-'a' + 1)%26 == s[i]-'a')
                prev += 1;
            else prev = 1;

            if (cnt[s[i]-'a'] < prev) {
                cnt[s[i]-'a'] = prev;
            }
        }
        return accumulate(cnt.begin(), cnt.end(), 0);        
    }
};