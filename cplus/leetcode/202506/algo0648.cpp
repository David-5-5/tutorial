#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 6.1 字典树（trie）- 基础
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
    int findMinPrefix(string word) {
        auto node = root;
        int cnt = 0;
        for (auto c: word) {
            if (node->son[c-'a'] == nullptr) return 0;
            cnt ++;
            node = node->son[c-'a'];
            if (node->end) return cnt;
        }

        return 0;
    }    
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        string ans = "";
        
        for (auto& word : dictionary) insert(word);

        sentence += " ";    // sentinel character
        size_t start = 0, end = 0;
        while ((end=sentence.find(' ', start)) != string::npos) {
            string word = sentence.substr(start, end-start);
            int pre_len = findMinPrefix(word);

            ans += " " + (pre_len==0?word:word.substr(0, pre_len));
            start = end + 1;
        }
        return ans.substr(1);
    }
};