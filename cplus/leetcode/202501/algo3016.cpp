#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumPushes(string word) {
        // 自行解答
        int cnt[26] = {0};
        for (char ch : word)
            cnt[ch-'a'] += 1;

        sort(cnt, cnt+26);
        reverse(cnt, cnt+26);

        int ans = 0;
        for (int i=0; i<26; i++) {
            ans += cnt[i] * ((i+8) / 8); // 上取整
        }
        return ans;    
    }   
};