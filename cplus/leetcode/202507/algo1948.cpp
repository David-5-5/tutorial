#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 6.2 字典树（trie）- 进阶
struct Node {
    // 使用 unordered_map 需要排序 paths
    map<string, Node*> son;     // 按目录排序 子目录序列化一致
    // 节点 x 的子节点 y1, y2, ... yk
    // serial(x) = y1(serial(y1))y2(serial(y2))...yk(serial(yk))
    string serial;  // 子节点的序列化表示使用括号表示法
};

class Solution {
private:
    Node* root = new Node();
    void insert(vector<string> path) {
        auto node = root;
        for (auto dir : path) {
            if (!node->son.count(dir)) node->son[dir] = new Node();
            node = node->son[dir];
        }
    }
public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        unordered_map<string, int> cnt;
        // 参考题解，和题解基本思路一致，就是如何children的序列化标识如何实现有疑问
        for (auto path: paths) {
            insert(path);
        }

        // Serial the children
        auto dfs = [&](this auto&& dfs, Node* node) -> void {
            string ser = "";
            for (auto& [key, chd_node]: node->son)  {
                dfs(chd_node);  // 递归
                ser += key + "("+chd_node->serial+")";
            }
            if (ser.length()>0) cnt[ser] ++;
            node->serial = ser;
        };
        
        dfs(root);
        vector<vector<string>> ans;

        auto output = [&](this auto&& output, Node* node, vector<string> path) -> void {
            for (auto& [key, chd_node]: node->son) {
                // cout << key << ", " << 
                if (chd_node->serial =="" || cnt[chd_node->serial] < 2) {
                    path.push_back(key);
                    ans.push_back(path);
                    output(chd_node, path);
                    path.pop_back();
                }
            }
        };
        vector<string> path;
        output(root, path);

        return ans;
    }
};