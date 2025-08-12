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
class BSTIterator {
private:
    deque<int> que;
public:
    BSTIterator(TreeNode* root) {
        auto dfs = [&](this auto dfs, TreeNode* node) -> void{
            if (!node) return;
            dfs(node->left);
            que.push_back(node->val);
            dfs(node->right);
        };
        dfs(root);
    }
    
    int next() {
        int val = que.front(); que.pop_front();
        return val;
    }
    
    bool hasNext() {
        return !que.empty();
    }
};

// 参考题解的写法
class BSTIterator {
private:
    int inx;
    vector<int> arr;
    vector<int> init(TreeNode* root) {
        vector<int> res;
        auto dfs = [&](this auto dfs, TreeNode* node) -> void{
            if (!node) return;
            dfs(node->left);
            res.push_back(node->val);
            dfs(node->right);
        };
        dfs(root); return res;
    };
        
public:
    BSTIterator(TreeNode* root):inx(0), arr(init(root)) {
    }
    
    int next() {
        return arr[inx++];
    }
    
    bool hasNext() {
        return (inx < (int) arr.size());
    }
};


// 进阶写法，用栈
class BSTIterator {
private:
    int inx;
    stack<TreeNode*> st;
    void push(TreeNode* root) {
        auto cur = root;
        while (cur) {
            st.push(cur); cur = cur->left;
        }
    };
        
public:
    BSTIterator(TreeNode* root) {
        push(root);
    }
    
    int next() {
        auto cur = st.top(); st.pop(); push(cur->right);
        return cur->val;
    }
    
    bool hasNext() {
        return !st.empty();
    }
};