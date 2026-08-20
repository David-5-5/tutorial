#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canConstruct(string s, int k) {
        int n = s.length(); vector<int> cnt(26);
        for (int i=0; i<n; i++) cnt[s[i] - 'a'] ++;
        int odds = 0;
        for (int i=0; i<26; i++) if (cnt[i]%2) odds ++;

        if (k>=odds && k<=n) return true;
        else return false;
        
    }
};