#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 构造题
class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        vector<int> cnt(26);

        for (auto ch:s) cnt[ch-'a'] ++;

        string ans;
        int first = 25, second = 25;
        
        while (true) {
            while (first>=0 && cnt[first]==0) first--;
            if (first>=0) {
                int time = min(cnt[first], repeatLimit);
                // 字符 转 字符串 直接循环
                for (int i=0; i<time; i++) ans += 'a' + first; 
                cnt[first] -= time;
            } else break;

            if (cnt[first]) {
                second = first - 1;
                while (second>=0 && cnt[second]==0) second--;
                if (second>=0) {
                    ans += 'a' + second, cnt[second]--;
                }else break;
            }
        }

        return ans;

    }
};