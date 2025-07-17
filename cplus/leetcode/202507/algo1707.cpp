#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 6.4 字典树（trie）- 0-1 字典树（异或字典树）
struct Node {
    Node* son[2]{};
};

class Solution {
private:
    const int hi = 29;
    Node* root = new Node();
    void insert(int val) {
        auto node = root;
        for (int i=hi; i>=0; --i) {
            int v = (val >> i) & 1;
            if (node->son[v] == nullptr) node->son[v] = new Node();
            node = node->son[v];
        }
    }
    int max_xor(int val) {
        int res = 0;
        auto node = root;
        for (int i=hi; i>=0; --i) {
            int v = (val >> i) & 1;
            if (node->son[v^1] != nullptr) {
                res |= 1 << i; node = node->son[v^1];
            }else if (node->son[v] != nullptr)
                node = node->son[v];
            else return -1;
        }
        return res;
    }
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        // 自行解答
        sort(nums.begin(), nums.end());
        int m = queries.size(), idx[m];
        iota(idx, idx+m, 0);
        sort(idx, idx + m, [&](int i, int j) {
            return queries[i][1] < queries[j][1];
        });

        vector<int> ans(m);
        int l = 0, n = nums.size();

        for (int i=0; i<m; i++) {
            auto q = queries[idx[i]];
            while (l < n && nums[l] <= q[1]) {
                insert(nums[l++]);
            }
            ans[idx[i]] = max_xor(q[0]);
        }
        return ans;
    }
};