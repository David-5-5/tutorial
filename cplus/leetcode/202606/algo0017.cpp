#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        unordered_map<char, string> d2l{ {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, 
             {'5', "jkl"}, {'6', "mno"},  {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};

        vector<string> ans;
        auto dfs = [&](this auto&& dfs, int i, string& path) -> void {
            if (i == digits.length()) ans.emplace_back(path);
            
            for (auto ch : d2l[digits[i]]) {
                path[i] = ch;
                dfs(i+1, path);
            }
        };

        string path(digits.length(), ' ');
        dfs(0, path);
        return ans;
    }

};