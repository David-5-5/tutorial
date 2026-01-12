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


    int longestCommonPrefix2(vector<int>& arr1, vector<int>& arr2) {
        // 使用整数的set
        set<int> prefixs;
        for (auto v: arr1) {
            while (v) {
                prefixs.insert(v); v /= 10;
            }
        }

        int ans = 0;
        for (auto v: arr2) {
            while (v) {
                if (prefixs.count(v)) {
                    ans = max(ans, (int)log10(v) + 1);
                    break;
                }
                v /= 10;
            }
        }
        return ans;
    }    
};