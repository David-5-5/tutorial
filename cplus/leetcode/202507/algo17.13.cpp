#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 6.3 字典树（trie）- 字典树优化 DP
struct Node {
    Node* son[26]{};
    bool end = false;
};

class Solution {
private:
    Node* root = new Node();
    void insert(string word) {
        auto node = root;
        for (auto c : word) {
            if (node->son[c-'a'] == nullptr) node->son[c-'a'] = new Node();
            node = node->son[c-'a'];
        }
        node->end = true;
    }

public:
    int respace(vector<string>& dictionary, string sentence) {
        int n = sentence.length();

        for (auto& word: dictionary) {
            insert(word);
        }

        auto find = [&](int s) -> vector<int> {
            vector<int> ans; auto node = root;
            for (int i=s; i<n; ++i) {
                if (node->son[sentence[i]-'a']==nullptr) break;
                node = node->son[sentence[i]-'a'];
                if (node->end) ans.push_back(i-s+1);
            }

            return ans;
        };

        vector<int> memo(n, -1);
        auto dfs = [&](this auto&& dfs, int i) -> int {
            if (i == n) return 0;
            auto& res = memo[i];
            if (res != -1) return res;
            res = 1 + dfs(i+1);         // 不选
            auto nexts = find(i);
            for (auto& l : nexts) {
                res = min(res, dfs(i+l));
            }
            return res;
        };

        return dfs(0);
    }
};
