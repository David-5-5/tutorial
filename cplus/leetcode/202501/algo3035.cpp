#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int maxPalindromesAfterOperations(vector<string>& words) {
        map<int, int> len_cnt;
        unordered_map<char, int> char_cnt;

        for (auto& word :words) {
            len_cnt[word.size()] += 1;
            for (auto& ch : word)
                char_cnt[ch] += 1;
        }
        
        int pairs = 0;
        for (auto it = char_cnt.begin(); it != char_cnt.end(); ++it) {
            pairs += it->second / 2;
        }

        return 0;
    }
};