#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 6.1 字典树（trie）- 基础
struct Node {
    Node* son[26]{};
    set<string> prefixs;
};

class Solution {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        // 不需要 Trie，
        sort(folder.begin(), folder.end());

        vector<string> ans;
        auto del = [&]() {
            while (true) {
                int n = ans.size(); if (n < 2) return;
                // 末尾添加 '/' 避免出现 /a/cd/d 是 /a/c 的子目录
                int ffl = ans[n-2].length()+1;  
                string parent = ans.back().substr(0, ans.back().rfind("/")+1);
                if (parent.length() >= ffl && parent.substr(0, ffl) == ans[n-2]+"/"){
                    ans.pop_back();
                }
                else return;
            }
        };

        for (auto f: folder) {
            if (ans.size() && (f.length() > ans.back().length() 
                        || f.substr(0, ans.back().length()) != ans.back())) {
                // 肯定不是子目录的情况下，清除 ans 中子目录
                del();
            }
            ans.push_back(f);
        }
        del();

        return ans;   
    }


};