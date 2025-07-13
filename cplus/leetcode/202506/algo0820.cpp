#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 6.1 字典树（trie）- 基础
struct Node {
    Node* son[26]{};
};

class Solution {
private:
    Node *root = new Node();
    void insert(string word) {
        auto node = root;
        for (auto c : word) {
            if (node->son[c-'a'] == nullptr) node->son[c-'a'] = new Node();
            node = node->son[c-'a'];
        }
    }    
public:
    int minimumLengthEncoding(vector<string>& words) {
        for (auto w : words) {
            reverse(w.begin(), w.end()); insert(w);
        }

        int ans = 0;
        auto dfs = [&](this auto&& dfs, Node* node, int d) -> void{
            bool has_son = false;
            for (auto s:node->son) {
                if (s!=nullptr) {has_son = true; dfs(s, d+1);}
            }
            if (!has_son) ans += d;
        };

        dfs(root, 1);
        return ans;
    }
};