#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.2 脑筋急转弯
class Solution {
public:
    int minOperations(string s) {
        // 方法一
        vector<int> seen(26);
        for (auto & ch: s) if (seen[ch-'a'] == 0) {
            seen[ch-'a'] = 1;
        }
        for (int i=1; i<26; i++) {
            if (seen[i]) return 26 - i;
        }
        return 0;
    }
   
};