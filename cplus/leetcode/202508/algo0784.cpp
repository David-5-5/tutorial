#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.2 子集型回溯
class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        // 自行解答
        vector<string> ans;
        
        auto dfs = [&](this auto&& dfs, int i, string& cur) -> void {
            if (i == s.length()) {
                ans.push_back(cur);
                return;
            } 
            
            cur.push_back(s[i]);
            dfs(i+1, cur);
            cur.pop_back();
            if (s[i]>='a' && s[i]<='z') 
                cur.push_back(s[i]-'a'+'A');
            else if (s[i]>='A' && s[i]<='Z')
                cur.push_back(s[i]-'A'+'a');
            
            if (cur.length() == i+1) {
                dfs(i+1, cur);
                cur.pop_back();
            }
        };

        string cur = "";
        dfs(0, cur); return ans;     
    }
};