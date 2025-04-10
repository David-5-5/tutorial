#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.4 前缀异或和
class Solution {
public:
    int findTheLongestSubstring(string s) {
        // 自行解答
        const unordered_set<char> vowel({'a', 'e', 'i', 'o', 'u'});
        int n = s.length();
        vector<int> prex(n+1);
        for (int i=0; i<n; i++) 
            if (vowel.count(s[i]))
                prex[i+1] = prex[i] ^ (1 << (s[i]-'a'));
            else prex[i+1] = prex[i];
        

        int ans = 0;
        unordered_map<int, int> pos;
        for (int i=0; i<=n; i++) {
            if (pos.count(prex[i])) ans = max(ans, i-pos[prex[i]]);
            if (!pos.count(prex[i])) pos[prex[i]] = i;
        }
        return ans;
    }
};