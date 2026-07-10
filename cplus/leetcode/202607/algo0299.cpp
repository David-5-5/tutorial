#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string getHint(string secret, string guess) {
        vector<int> cnt(10); int n = secret.length();
        int bulls = 0, cows = 0;
        for (int i = 0; i<n; i++) {
            if (secret[i] == guess[i]) bulls ++;
            else {
                cnt[secret[i] - '0'] ++;
                cnt[guess[i] - '0'] --;
            }
        }
        cows = n - bulls;
        for (auto c: cnt) if (c>0) cows -= c;
        return to_string(bulls) + "A" + to_string(cows) + "B";
    }
};