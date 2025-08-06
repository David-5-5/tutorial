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
    TreeNode* sortedListToBST(ListNode* head) {
        // 基于 108 转换成 vector
        vector<int> nums;
        auto cur = head;
        while (cur) {nums.push_back(cur->val); cur = cur->next;}

        auto dfs = [&](this auto&& dfs, int l, int r) -> TreeNode* {
            if (l > r) return nullptr;
            int mid = l + (r - l)/2;
            return new TreeNode(nums[mid], dfs(l, mid-1), dfs(mid+1, r));
        };
        return dfs(0, nums.size()-1);
    }

    TreeNode* sortedListToBST(ListNode* head) {
        // 参考题解 快慢节点, 这个容易理解
        auto getMedian = [&](ListNode* left, ListNode* right) -> ListNode* {
            auto slow = left, fast = left;
            while (fast!=right && fast->next!=right) {
                slow = slow->next;
                fast = fast->next->next;
            }
            return slow;
        };
        
        auto build = [&](this auto&& build, ListNode* left, ListNode* right) -> TreeNode* {
            if (left == right) return nullptr;
            ListNode* mid = getMedian(left, right);
            TreeNode* root = new TreeNode(mid->val);
            root->left = build(left, mid);
            mid = mid->next;
            root->right = build(mid, right);
            return root;
        };

        return build(head, nullptr);
        
    }


};