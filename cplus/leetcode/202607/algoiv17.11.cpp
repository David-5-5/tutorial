#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findClosest(vector<string>& words, string word1, string word2) {
        int w1_inx = INT_MIN / 2, w2_inx = INT_MIN /2 , ans = INT_MAX;
        for (int i=0; i<words.size(); i++) {
            if (words[i] == word1) {
                ans = min(ans, i-w2_inx); w1_inx = i;
            } else if (words[i] == word2) {
                ans = min(ans, i-w1_inx); w2_inx = i;
            }
        }
        return ans;
    }
};