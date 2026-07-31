#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node* son[26]{};
    bool end = false;
};

class Trie {
private:
    Node* root =  new Node();
public:
    Trie() {
    }
    
    void insert(string word) {
        auto node = root;
        reverse(word.begin(), word.end());
        for (auto c : word) {
            if (node->son[c-'a'] == nullptr) node->son[c-'a'] = new Node();
            node = node->son[c-'a'];
        }
        node->end = true;
    }
    
    bool find(vector<char>& s) {
        auto node = root;
        for (int i=s.size()-1; i>=0; i--) {
            if (node->son[s[i]-'a'] == nullptr) return false;
            node = node->son[s[i]-'a'];
            if (node->end) return true;
        }

        return false; 
    }
    
};

class StreamChecker {
private:
    vector<char> stream;
    Trie tree;
public:
    StreamChecker(vector<string>& words) {
        for (auto w: words) tree.insert(w);
    }
    
    bool query(char letter) {
        stream.emplace_back(letter);
        return tree.find(stream);
    }
};
