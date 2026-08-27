#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool reportSpam(vector<string>& message, vector<string>& bannedWords) {
        unordered_set<string> ban_hash(bannedWords.begin(), bannedWords.end());
        int cnt = 0;
        for (auto word : message) {
            if (ban_hash.count(word)) cnt ++;
        }
        return cnt >= 2;
    }
};