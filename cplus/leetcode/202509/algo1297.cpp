#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 定长滑动窗口 1.2 进阶
class Solution {
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        // 自行解答，这里有个贪心，满足条件的最短的子串，出现的次数会越大
        int l = 0, ans = 0, n = s.length();
        unordered_map<string, int> cnt;
        unordered_map<char, int> letters;

        for (int r=0; r<n; ++r) {
            letters[s[r]] ++;
            if (r-l+1 < minSize) continue;
            // else if (r-l+1 <= maxSize && letters.size() <= maxLetters) {
            else if (letters.size() <= maxLetters) { // maxSize 多余     
                cnt[s.substr(l, r-l+1)] ++;
                ans = max(ans, cnt[s.substr(l, r-l+1)]);
            }
            letters[s[l]] --;
            if (letters[s[l]] == 0) letters.erase(s[l]);
            l ++;               
        }
        return ans;       
    }
};