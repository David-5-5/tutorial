#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node* son[26]{};
    bool end = false;
};

// 回溯 - 4.7 搜索
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
    
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // 复习，自行解答 字典树
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        vector<string> ans;
        for (auto w:words) insert(w);
        int m = board.size(), n = board[0].size(); 

        vector<vector<bool>> vis(m, vector<bool>(n));

        auto dfs = [&](this auto&& dfs, int i, int j, Node* node, string& path) -> void {            
            auto ch = board[i][j];
            if (node->son[ch-'a'] == nullptr) return;
            
            path.push_back(ch);

            if (node->son[ch-'a']->end) {
                ans.push_back(path); node->son[ch-'a']->end = false;    // 仅需要增加一次
            }
            vis[i][j] = true;
            
            for (int k=0; k<4; ++k) {
                auto i_ = i + dirs[k][0], j_ = j + dirs[k][1];
                if (i_ >= 0 && i_<m && j_>=0 && j_<n && !vis[i_][j_]) {
                    dfs(i_, j_, node->son[ch-'a'], path);
                }
            }
            vis[i][j] = false;
            path.pop_back();
        };
        
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            string path = "";
            dfs(i, j, root, path);
        }

        return ans;
    }

};