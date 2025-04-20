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

    int findTheLongestSubstring2(string s) {
        // 一次遍历
        // 初始化 unordered_set
        const unordered_set<char> vowel({'a', 'e', 'i', 'o', 'u'});
        // 初始化 unordered_map
        // unordered_map<char, int> vowel{{'a',0}, {'e',1}, {'i',2}, {'o',3}, {'u',4}};
        int n = s.length();

        int ans = 0, prex = 0;
        unordered_map<int, int> pos;
        pos[prex] = -1;
        for (int i=0; i<n; i++) {
            if (vowel.count(s[i])) prex ^= 1 << (s[i] - 'a');
            if (pos.count(prex)) ans = max(ans, i-pos[prex]);
            if (!pos.count(prex)) pos[prex] = i;
            
        }
        return ans;
    }

    int findTheLongestSubstring3(string s) {
        // 一次遍历
        int n = s.length();

        int ans = 0, prex = 0;
        unordered_map<int, int> pos;
        pos[prex] = -1;
        for (int i=0; i<n; i++) {
            if (s[i]=='a') prex ^= 1 << 0;
            else if (s[i]=='e') prex ^= 1 << 1;
            else if (s[i]=='i') prex ^= 1 << 2;
            else if (s[i]=='o') prex ^= 1 << 3;
            else if (s[i]=='u') prex ^= 1 << 4;

            if (pos.count(prex)) ans = max(ans, i-pos[prex]);
            if (!pos.count(prex)) pos[prex] = i;
            
        }
        return ans;
    }
};