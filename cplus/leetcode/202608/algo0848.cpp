#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string shiftingLetters(string s, vector<int>& shifts) {
        int n = s.length(), suf = 0;
        for (int i=n-1; i>=0; i--) {
            suf = (suf + shifts[i]) % 26;
            s[i] = ((s[i] - 'a' + suf) % 26) + 'a';
        }

        return s;
    }
};