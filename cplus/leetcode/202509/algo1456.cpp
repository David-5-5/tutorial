#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 定长滑动窗口 1.1 基础
class Solution {
public:
    int maxVowels(string s, int k) {
        // 滑动窗口 自行解答
        set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        int cnt = 0, ans = 0;
        for (int i=0; i<k-1; ++i) {
            // cout << s[i] << endl;
            if (vowels.count(s[i])) cnt ++;
        }

        for (int i=k-1; i<s.length(); i++) {
            if (vowels.count(s[i])) cnt++;
            ans = max(ans, cnt);
            if (vowels.count(s[i-k+1])) cnt--;
        }
        return ans;        
    }
};