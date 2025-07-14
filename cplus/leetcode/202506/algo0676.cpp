#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 6.2 字典树（trie）- 进阶
struct Node {
    Node* son[26]{};
    bool end = false;
  
};

// 自行解答
class MagicDictionary {
private:
    Node *root = new Node();
    
    void insert(string word) {
        auto node = root;
        for (auto c : word) {
            if (node->son[c-'a'] == nullptr) node->son[c-'a'] = new Node();
            node = node->son[c-'a'];
        }
        node->end = true;
    }  
public:
    MagicDictionary() {
        
    }
    
    void buildDict(vector<string> dictionary) {
        for (auto d : dictionary) insert(d);
    }
    
    bool search(string searchWord) {
        int n = searchWord.length();

        auto dfs = [&](this auto&& dfs, int i, Node* cur, bool chg) -> bool{
            if (i == n) return cur->end && chg;
            auto c = searchWord[i];
            
            if (cur->son[c-'a']== nullptr && chg) return false;

            if (cur->son[c-'a']!= nullptr && dfs(i+1, cur->son[c-'a'], chg)) return true;        // 不改
            if (!chg) {                                                                          // 改
                for (auto ch : cur->son) 
                    if (ch!=nullptr && ch!=cur->son[c-'a'] && dfs(i+1, ch, true)) return true;      
            }
            return false;       
        };

        return dfs(0, root, false);
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */