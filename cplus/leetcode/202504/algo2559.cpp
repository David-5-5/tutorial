#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.1 前缀和基础
class Solution {
public:
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
        // 自行解答，前缀和
        unordered_set<char> vowel({'a', 'e', 'i', 'o', 'u'});

        int n = words.size();
        vector<int> pres(n+1, 0);

        for (int i=0; i<n; i++) {
            auto& e = words[i];
            pres[i+1] = pres[i] + (vowel.count(e[0]) && vowel.count(e[e.length()-1]));
        }

        vector<int> ans;
        for (auto& q: queries) {
            ans.push_back(pres[q[1]+1]-pres[q[0]]);
        }
        return ans;     
    }
};