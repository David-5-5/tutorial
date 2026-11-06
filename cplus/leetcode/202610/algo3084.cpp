#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countSubstrings(string s, char c) {
        int n = 0; for (auto & ch : s) if (ch == c) n ++;
        return n * (n + 1) /2;
    }
    
    long long countSubstrings(string s, char c) {
        long long ans = 0; int n = 0; 
        for (auto & ch : s) if (ch == c) {n ++; ans += n;}
        return ans;
    }
};