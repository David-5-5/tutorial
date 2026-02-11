#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.5 划分型贪心
class Solution {
public:
    int maxSubstrings(string word) {
        // 自行解答
        int ans = 0, n = word.length();
        vector<int> first(26, -1);
        for (int i=0; i<n; ++i) {
            int ids = word[i] - 'a';
            if (first[ids] == -1) {
                first[ids] = i;
            } else {
                if (i - first[ids] + 1 >= 4) {
                    ans ++; fill(first.begin(), first.end(), -1);
                }
            }
        }
        
        return ans;   

    }
};