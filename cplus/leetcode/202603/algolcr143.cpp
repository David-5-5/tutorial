#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 */
// LCR series
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if (B == nullptr || A == nullptr) return false;
        auto check = [&](this auto&& check, TreeNode* a, TreeNode* b) -> bool {
            if (b == nullptr) return true;
            if (b != nullptr && a == nullptr) return false;
            return a->val == b->val && check(a->left, b->left) && check(a->right, b->right);
        };

        return check(A, B) || isSubStructure(A->left, B) || isSubStructure(A->right, B);
    }
};