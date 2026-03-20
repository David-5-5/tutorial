#include <bits/stdc++.h>
using namespace std;

// 三、字符串贪心 - 3.1 字典序最小/最大
class Solution {
public:
    string answerString(string word, int numFriends) {
        // 自行解答 性能稍优
        vector<vector<int>> pos(26); int mx = 0, n = word.length();
        if (numFriends == 1) return word;

        for (int i=0; i<n; i++) {
            auto ch = word[i] - 'a';
            pos[ch].push_back(i); if (ch > mx) mx = ch;
        }
        
        // 取最大的字符枚举最大的可能长度
        // if (pos[mx].size() == n) return word.substr(0, n-numFriends+1);
        string ans = "";
        for (auto p: pos[mx]) {
            ans = max(ans, word.substr(p, n-max(p, numFriends-1)));
        }
        return ans;
    }

    string answerString(string word, int numFriends) {
        // 直接枚举
        int n = word.length();
        if (numFriends == 1) return word;
        
        string ans = "";
        for (int i=0; i<n; i++) {
            ans = max(ans, word.substr(i, n-max(i, numFriends-1)));
        }
        return ans;
    }        
};