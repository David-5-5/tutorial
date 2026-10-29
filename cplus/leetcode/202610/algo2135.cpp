#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int wordCount(vector<string>& startWords, vector<string>& targetWords) {
        set<int> h_start;
        
        for (auto &w: startWords) {
            int w_int = 0;
            for (auto & ch: w) {
                w_int |= 1 << (ch - 'a');
            }
            h_start.emplace(w_int);
        }

        int ans = 0;
        for (auto &w: targetWords) {
            int w_int = 0;
            for (auto & ch: w) {
                w_int |= 1 << (ch - 'a');
            }
            
            for (auto &ch: w) {
                if (h_start.count(w_int ^ 1 << (ch - 'a'))) {
                    ans ++; break;
                }
            }
        }
        return ans;
    }
};