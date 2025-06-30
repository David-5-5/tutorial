#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 6.1 字典树（trie）- 基础
struct Node {
    unordered_map<int, Node*> son;
};

class Solution {
private:
    Node *root = new Node();
    void insert(vector<int>& arr, int l, int r) {
        auto node = root;
        for (int i=l; i<=r; i++) {
            int c = arr[i];
            if (node->son[c] == nullptr) node->son[c] = new Node();
            node = node->son[c];
        }
    }
public:
    int countDistinct(vector<int>& nums, int k, int p) {
        // 自行解答，直接用字典树去重 O(n^2) 时间复杂度
        int n = nums.size();
        int cnt = 0, r = n-1;
        for (int l=n-1; l>=0; --l) {
            if (nums[l] % p == 0) cnt ++;
            while (cnt > k) {
                if (nums[r]%p == 0) cnt--;
                r --;
            }
            insert(nums, l, r); 
        }
        
        auto dfs = [&](this auto&& dfs, Node* node) -> int {
            int res = 1;
            for (auto [_, s]: node->son) {
                res += dfs(s);
            }
            return res;
        };

        return dfs(root) - 1;
    }

};