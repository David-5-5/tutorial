#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 6.1 字典树（trie）- 基础
struct oi_trie {
  int nex[100000][26] = {0}, cnt = 0;
  bool exist[100000] = {false};  // 该结点结尾的字符串是否存在

  void insert(char *s, int l) {  // 插入字符串
    int p = 0;
    for (int i = 0; i < l; i++) {
      int c = s[i] - 'a';
      if (!nex[p][c]) nex[p][c] = ++cnt;  // 如果没有，就添加结点
      p = nex[p][c];
    }
    exist[p] = true;
  }

  bool find(char *s, int l) {  // 查找字符串
    int p = 0;
    for (int i = 0; i < l; i++) {
      int c = s[i] - 'a';
      if (!nex[p][c]) return 0;
      p = nex[p][c];
    }
    return exist[p];
  }

  bool findPrefix(char *s, int l) {  // 查找字符串
    int p = 0;
    for (int i = 0; i < l; i++) {
      int c = s[i] - 'a';
      if (!nex[p][c]) return false;
      p = nex[p][c];
    }
    return true;
  }

};

class Trie {
private:
    oi_trie trie;
public:
    Trie() {
    }
    
    void insert(string word) {
        trie.insert(word.data(), word.length());
    }
    
    bool search(string word) {
        return trie.find(word.data(), word.length());
    }
    
    bool startsWith(string prefix) {
        return trie.findPrefix(prefix.data(), prefix.length());
    }
};

// 实现二
// Trie 模板题
struct Node {
    Node* son[26]{};
    bool end = false;
};

class Trie {
private:
    Node* root =  new Node();
    int find(string word) {
        auto node = root;
        for (auto c: word) {
            if (node->son[c-'a'] == nullptr) return 0;
            node = node->son[c-'a'];
        }

        return node->end?2:1;
    }
public:
    Trie() {
    }
    
    void insert(string word) {
        auto node = root;
        for (auto c : word) {
            if (node->son[c-'a'] == nullptr) node->son[c-'a'] = new Node();
            node = node->son[c-'a'];
        }
        node->end = true;
    }
    
    bool search(string word) {
        return find(word) == 2;
    }
    
    bool startsWith(string prefix) {
        return find(prefix);
    }
};


/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */