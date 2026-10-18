#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs) {
        unordered_map<char, int> cnt;
        unordered_map<char, char> prev = {{'r','c'}, {'o','r'}, {'a','o'}, {'k','a'}};

        int ans = 0, croaks = 0;
        for (auto c: croakOfFrogs) {
            if (c == 'c') {
                croaks ++;
                cnt[c] += 1; ans = max(ans, croaks);
            } else if (c == 'r' || c == 'o' || c == 'a') {
                cnt[prev[c]] --; if (cnt[prev[c]] < 0) return -1;
                cnt[c] += 1;
            } else { // c == 'k'
                cnt[prev[c]] --; croaks --;
            }
        }
        for (auto &[_, c]: cnt) if (c != 0) return -1;
        return ans;  
    }
};