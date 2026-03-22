#include <bits/stdc++.h>
using namespace std;

// 三、字符串贪心 - 3.1 字典序最小/最大
class Solution {
public:
    string smallestPalindrome(string s) {
        // 自行解答 
        int n = s.length();
        string pre = s.substr(0, n/2);
        string mid = ""; if (n%2) mid = s.substr(n/2,1);
        sort(pre.begin(), pre.end()); 
        string suf(pre.rbegin(), pre.rend());
        return pre + mid + suf;        
    }

    string smallestPalindrome(string s) {
        // 参考题解 计数排序
        int n = s.length();
        string ans = ""; if (n%2) ans = s.substr(n/2,1);
        vector<int> cnt(26);
        for (int i=0; i<n/2; i++) {
            cnt[s[i]-'a'] += 1;
        }
        for (int i=25; i>=0; i--) ans = string(cnt[i], 'a' + i) + ans + string(cnt[i], 'a' + i);
        return ans;
    }
};