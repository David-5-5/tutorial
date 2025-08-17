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

// 二叉树 - 2.16 其他
class Solution {
public:
    int countNodes(TreeNode* root) {
        // 参考题解，二分查找
        int h = 0;
        if (!root) return 0;
        auto cur = root;
        while (cur->left) {h++, cur= cur->left;}

        auto left = (1 << h) - 1, right = 1 << (h+1);
        
        auto check = [&](int m) -> bool {
            auto cur = root;
            for (int i=h; i; --i) {
                if (m >> (i-1) & 1) {
                    if (cur->right) cur = cur->right;
                    else return false;
                } else {
                    if (cur->left) cur = cur->left;
                    else return false;
                }
            }
            
            return true;
        };

        while (left + 1 < right) { // 区间不为空
            int mid = left + (right - left) / 2;
            if (check(mid)) {
                left = mid; // 范围缩小到 (mid, right)
            } else {
                right = mid; // 范围缩小到 (left, mid)
            }
        }
        return left;

    }
};