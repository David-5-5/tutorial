#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 6.2 字典树（trie）- 进阶
struct Node {
    Node* son[26]{};
    int result = 0;
};
// 内存防爆 - 参考题解
void dfs_free(Node* node) {
    for (int i = 0; i < 26; i++) {
        if (node->son[i]) {
            dfs_free(node->son[i]);
        }
    }
    delete node;
}

class Solution {
private:
    Node *root = new Node();

public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        // 自行解答 - 没有 dfs_free 内存会溢出
        auto insert = [&](int i) {
            auto node = root;
            if (wordsContainer[i].length() < wordsContainer[node->result].length()){
                node->result = i;
            }
            reverse(wordsContainer[i].begin(), wordsContainer[i].end());
            for (auto& c : wordsContainer[i]) {
                if (node->son[c-'a'] == nullptr) {
                    node->son[c-'a'] = new Node(); node->son[c-'a']->result = i;
                }
                node = node->son[c-'a'];
                if (wordsContainer[i].length() < wordsContainer[node->result].length()){
                    node->result = i;
                }
            }
        };

        for (int i=0; i<wordsContainer.size(); ++i) {
            insert(i);
        }

        vector<int> ans;
        for (auto& q: wordsQuery) {
            auto query = [&]() -> void {
                auto node = root;
                reverse(q.begin(), q.end());
                for (auto& c: q) {
                    if (node->son[c-'a'] == nullptr) break;
                    node = node->son[c-'a'];
                }
                ans.push_back(node->result);
            };
            query();
        }
        dfs_free(root);
        return ans;
    }

    vector<int> stringIndices2(vector<string>& wordsContainer, vector<string>& wordsQuery) {

        for (int i=0; i<wordsContainer.size(); ++i) {
            auto node = root;
            if (wordsContainer[i].length() < wordsContainer[node->result].length()){
                node->result = i;
            }
            
            for (int j=wordsContainer[i].length()-1; j>=0; --j) {
                auto & c = wordsContainer[i][j];
                if (node->son[c-'a'] == nullptr) {
                    node->son[c-'a'] = new Node(); node->son[c-'a']->result = i;
                }
                node = node->son[c-'a'];
                if (wordsContainer[i].length() < wordsContainer[node->result].length()){
                    node->result = i;
                }
            }
        }

        vector<int> ans;
        for (auto& q: wordsQuery) {
            auto node = root;
            
            for (int i=q.length()-1; i>=0; --i) {
                auto& c= q[i];
                if (node->son[c-'a'] == nullptr) break;
                node = node->son[c-'a'];
            }
            ans.push_back(node->result);
        }
        dfs_free(root);
        return ans;
    }
};