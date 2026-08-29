#include <bits/stdc++.h>
using namespace std;

// AC 自动机
struct Node {
    Node* son[26]{};
    Node* fail;
    bool end = false;
};

class StreamChecker {
private:
    Node* root;
    Node* cur;
public:
    StreamChecker(vector<string>& words) {
        root = new Node();
        for (auto word: words) {
            auto node = root;
            for (auto c : word) {
                if (node->son[c-'a'] == nullptr) node->son[c-'a'] = new Node();
                node = node->son[c-'a'];
            }
            node->end = true;
        }

        queue<Node*> q;
        for (int i=0; i<26; i++) {
            if (root->son[i] != nullptr) {
                root->son[i]->fail = root; q.emplace(root->son[i]);
            }  else root->son[i] = root;
        }

        while (!q.empty()) {
            Node* node = q.front(); q.pop();
            node->end = node->end || node->fail->end;
            for (int i=0; i<26; i++) {
                if (node->son[i] != nullptr) {
                    node->son[i]->fail = node->fail->son[i];
                    q.emplace(node->son[i]);
                } else node->son[i] = node->fail->son[i];
            }
        }
        cur = root;
    }
    
    bool query(char letter) {
        cur = cur->son[letter-'a'];
        return cur->end;
    }
};

