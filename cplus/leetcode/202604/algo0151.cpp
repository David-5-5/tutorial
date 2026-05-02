#include <bits/stdc++.h>
using namespace std;

// 顺序
class Solution {
public:
    string reverseWords(string s) {
        vector<string> res;
        stringstream ss(s);
        string word;
        while (ss >> word) res.push_back(word);
        reverse(res.begin(), res.end());
        
        string ans = res.size()?res[0]:"";
        for (int i=1; i<res.size(); ++i) ans += " " + res[i];
        return ans;

    }
};