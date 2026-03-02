#include <bits/stdc++.h>
using namespace std;

// 同 677
struct Node {
    Node* son[26]{};
    int val = 0;
};

// 自行解答
class MapSum {
private:
    Node *root = new Node();
public:
    MapSum() {
        
    }
    
    void insert(string key, int val) {
        auto node = root;
        for (auto c : key) {
            if (node->son[c-'a'] == nullptr) node->son[c-'a'] = new Node();
            node = node->son[c-'a'];
        }
        node->val = val;
    }

    int sum(string prefix) {
        auto node = root;
        for (auto c: prefix) {
            if (node->son[c-'a'] == nullptr) return 0;
            node = node->son[c-'a'];
        }
        
        auto dfs = [](this auto&& dfs, Node* cur) -> int {
            int res = cur->val;
            for (auto ch : cur->son) {
                if (ch!=nullptr) res += dfs(ch);
            }
            return res;
        };

        return dfs(node);
    }
};
