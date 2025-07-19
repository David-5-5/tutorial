#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 二叉树 - 2.5 有递有归
class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        // 自行解答

        auto dfs = [&] (this auto&& dfs, TreeNode* node, int gr) -> int {

            // 后序遍历，先右子树，后左子树
            // cur 为当前节点， left right 为左右子树节点之和
            int cur = node->val, right = 0, left = 0;
            if(node->right) right = dfs(node->right, gr);   // gr
            node->val += right + gr;                // 更新节点值
            if (node->left)  {
               left = dfs(node->left, node->val);   // 将父节点+右子树的值加到左子树上
            } 

            return cur + right + left;  // 子树的值之和
        };
        dfs(root, 0);
        return root; 
    }
};