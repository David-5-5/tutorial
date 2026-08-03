#include <bits/stdc++.h>
using namespace std;

// AC 自动机
struct Node {
    Node* son[26]{};
    Node* fail;
    bool end = false;
    int len = 0, idx = -1;
};

class Solution {
private:
    Node * root;
public:
    vector<vector<int>> multiSearch(string big, vector<string>& smalls) {
        auto kmp = [](string str, string pat) -> vector<int> {
            int n = str.size(), m = pat.size();
            vector<int> p_pi(m);
            for (int i=1; i < m; i++) {
                int j = p_pi[i-1];
                while (j > 0 && pat[j]!=pat[i])
                    j = p_pi[j-1];
                if (pat[j] == pat[i])
                    p_pi[i] = j + 1;
                else p_pi[i] = j;
            }

            vector<int> ans;
            int j = 0;
            for (int i=0; i<n; i++) {
                while (j > 0 && str[i] != pat[j])
                    j = p_pi[j-1];
                if (str[i] == pat[j]) j++;
                if (j == m) ans.push_back(i-j+1), j = p_pi[j-1];
            }

            return ans;
        }; 
        
        vector<vector<int>> ans;
        for (auto & s: smalls) {
            if (s.length())
                ans.emplace_back(kmp(big, s));
            else ans.push_back({});
        }
        return ans;
    }

    vector<vector<int>> multiSearch2(string big, vector<string>& smalls) {
        root = new Node(); int n = smalls.size();
        for (int i=0; i<n; i++) {
            auto & word = smalls[i];
            auto node = root;
            for (auto c : word) {
                if (node->son[c-'a'] == nullptr) node->son[c-'a'] = new Node();
                node = node->son[c-'a'];
            }
            node->end = true, node->len = word.length(), node->idx = i;
        } 
        queue<Node*> q;
        for (int i=0; i<26; i++) {
            if (root->son[i] != nullptr) {
                root->son[i]->fail = root; q.emplace(root->son[i]);
            }  else root->son[i] = root;
        }

        while (!q.empty()) {
            Node* node = q.front(); q.pop();
            // node->end = node->end || node->fail->end;    // 和 1032 差异，一点点体会
            for (int i=0; i<26; i++) {
                if (node->son[i] != nullptr) {
                    node->son[i]->fail = node->fail->son[i];
                    q.emplace(node->son[i]);
                } else node->son[i] = node->fail->son[i];
            }
        }
        auto cur = root; vector<vector<int>> ans(n);

        for (int i=0; i<big.length(); i++) {
            auto & c = big[i];
            cur = cur->son[c - 'a'];
            if (cur == nullptr) break;
            auto fail = cur;
            while (fail != nullptr && fail != root) {
                if (fail->end) ans[fail->idx].emplace_back(i+1-fail->len);
                fail = fail->fail;
            }
        }

        return ans;
    }    
};

int main() {
    string big = "mississippi"; vector<string> smalls = {"is","ppi","hi","sis","i","ssippi"};
    Solution().multiSearch2(big, smalls);
}