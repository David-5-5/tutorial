#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfSpecialChars(string word) {
        // 自行解答 状态机
        // state 0: initial, 1: lower, 2: upper, 3 -> illegal
        vector<int> state(26);

        for (auto& ch: word) {
            if (ch >= 'a' && ch <= 'z') {
                if (state[ch-'a'] == 0) state[ch-'a'] = 1;
                else if (state[ch-'a'] == 2) state[ch-'a'] = 3;
            } else {
                if (state[ch-'A'] == 0) state[ch-'A'] = 3;
                else if (state[ch-'A'] == 1) state[ch-'A'] = 2;
            }
        }

        int ans = 0;
        for (int &v: state) if (v == 2) ans ++;
        return ans;

    }
};