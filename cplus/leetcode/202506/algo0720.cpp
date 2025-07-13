#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 6.1 字典树（trie）- 基础
// 自行解答
struct Node {
    Node* son[26]{};
    // bool end = false;
    
};
class Solution {
private:    
    Node* root = new Node();
    
    bool insert(string word) {
        auto node = root; //root->end = true;
        for (int i=0; i<word.length(); ++i) {
            if (node->son[word[i]-'a'] == nullptr && i == word.length() -1 ) {
                node->son[word[i]-'a'] = new Node();
                node = node->son[word[i]-'a'];
            } else if (node->son[word[i]-'a'] != nullptr) node = node->son[word[i]-'a'];
            else return false;
        }
        return true;
    };

    
public:
    string longestWord(vector<string>& words) {
        sort(words.begin(), words.end(), [](string a, string b){
            return a.length() < b.length();
        });
        string ans = "";
        for (auto w : words) {
            if (insert(w)) {
                if (w.length() > ans.length()) ans = w;
                else if (w.length() == ans.length() && w < ans) ans = w;
            }
        }
        return ans;
    }
};