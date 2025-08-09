#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 二叉树 - 2.14 链表+二叉树
class Solution {
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        // 自行解答 - 记忆化搜索
        // 自定义哈希函数：将两个指针的哈希值组合
        struct PairHash {
            size_t operator()(const std::pair<ListNode*, TreeNode*>& p) const {
                // 分别计算两个指针的哈希值
                size_t hash1 = std::hash<ListNode*>()(p.first);
                size_t hash2 = std::hash<TreeNode*>()(p.second);
                
                // 组合两个哈希值（避免碰撞的简单方式）
                return hash1 ^ (hash2 << 1);
            }
        }; 
        unordered_map<pair<ListNode*, TreeNode*>, bool, PairHash> memo;

        auto dfs = [&] (this auto&& dfs, ListNode* cur, TreeNode* node) -> bool {
            if (!cur) return true; if (!node) return false;
            
            if (memo.count({cur, node})) return memo[{cur, node}];

            if (cur->val == node->val && (dfs(cur->next, node->left) || dfs(cur->next, node->right)))  {
                return memo[{cur, node}] = true;
            }
            return memo[{cur, node}] = dfs(head, node->left) || dfs(head, node->right);

        };
        return dfs(head, root);
    }
};