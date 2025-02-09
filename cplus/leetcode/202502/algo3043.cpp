#include <bits/stdc++.h>
using namespace std;

// The Trie class
struct Node {
    Node *son[10]{};
    int depth = 0;
};


// 周赛 385
class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        Node* root = new Node();
        
        for (auto& v:arr1) {
            auto str = to_string(v);
            auto cur = root;
            for (auto ch:str){
                int c = ch - '0';
                if (cur->son[c] == nullptr) {
                    cur->son[c] = new Node();
                    cur->son[c]->depth = cur->depth + 1;
                }
                cur = cur->son[c];
            }
        }

        int ans = 0;
        for (auto& v:arr2) {
            auto str = to_string(v);
            auto cur = root;
            for (auto ch:str) {
                int c = ch - '0';
                if (cur->son[c] != nullptr) cur = cur->son[c];
                else break;
            }
            ans = max(ans, cur->depth);
        }

        return ans;

    }
};