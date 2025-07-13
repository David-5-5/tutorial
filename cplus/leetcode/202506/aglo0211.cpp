#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 6.2 字典树（trie）- 进阶
struct Node {
    Node* son[26]{};
    bool end = false;
};

// 自行解答
class WordDictionary {
private:
    Node *root = new Node();
public:
    WordDictionary() {
        
    }
    
    void addWord(string word) {
        auto node = root;
        for (auto c : word) {
            if (node->son[c-'a'] == nullptr) node->son[c-'a'] = new Node();
            node = node->son[c-'a'];
        }
        node->end = true;
    }
    
    bool search(string word) {
        int n = word.length();
        auto dfs = [&](this auto&& dfs, int i, Node* cur) -> bool{
            if (i == n) return cur->end;
            auto c = word[i];
            if (c != '.') {
                if (cur->son[c-'a'] == nullptr) return false;
                else return dfs(i+1, cur->son[c-'a']);
            } else {
                for (auto ch : cur->son) {
                    if (ch!=nullptr && dfs(i+1, ch)) return true;
                }
                return false;
            }
        };

        return dfs(0, root);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */