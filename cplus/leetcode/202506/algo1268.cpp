#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 6.1 字典树（trie）- 基础
struct Node {
    Node* son[26]{};
    set<string> prefixs;
};

class Solution {
private:
    Node* root = new Node();
    void insert(string word) {
        auto node = root;
        for (auto c : word) {
            if (node->son[c-'a'] == nullptr) node->son[c-'a'] = new Node();
            node = node->son[c-'a'];
            node->prefixs.insert(word);
            if (node->prefixs.size() > 3) node->prefixs.erase(prev(node->prefixs.end()));
        }
    }
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        // 自行解答
        int n = searchWord.length();
        vector ans(n, vector<string>());

        for (auto p :products) insert(p);

        auto node = root;
        for (int i = 0; i<n; ++i) {
            auto ch = searchWord[i];
            if(node->son[ch-'a'] == nullptr) break;
            node = node->son[ch-'a'];
            for (auto it=node->prefixs.begin(); it!=node->prefixs.end(); ++it) ans[i].push_back(*it);
        }

        return ans;
    }
};