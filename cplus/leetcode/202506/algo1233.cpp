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

    vector<string> removeSubfolders2(vector<string>& folder) {
        // 不需要 Trie
        // 上面代码有个思维的错误，对于 /a /a/b /a/b/c 误以为，
        // 先把 /a/b 删除后 /a/b/c 无法删除，因此上面代码的逻辑是
        // 先删除 /a/b/c 再删除 /a/b，这是完全没有必要的，重新改写代码如下
        sort(folder.begin(), folder.end());

        vector<string> ans{folder[0]};

        for (int i = 1; i < folder.size(); ++i) {
            int pre = ans.back().length();
            if (folder[i].length() <= pre 
                    || !(folder[i].substr(0, pre) == ans.back()&& folder[i][pre] == '/')) {
                ans.push_back(folder[i]);
            }
        }
        return ans;   
    }
};