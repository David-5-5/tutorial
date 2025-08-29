#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 6.4 字典树（trie）- 0-1 字典树（异或字典树）
// 位运算 - 试填法
// BEGIN - 字典树 - 最大异或和模板
struct Node {
    Node* son[2]{};
    int cnt = 0;
};

class Solution {
private:
    const int hi = 31;          // 与题目的数组值域保持一致 int 31 long long 63
    Node* root = new Node();
    void insert(int val) {
        auto node = root;
        node->cnt ++;
        for (int i=hi; i>=0; --i) {
            int v = (val >> i) & 1;
            if (node->son[v] == nullptr) node->son[v] = new Node();
            node = node->son[v];
            node->cnt ++;
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
            else return -1; // 仅当字典树中元素为空时
        }
        return res;
    } 
// END - 最大异或和模板
public:
    int findMaximumXOR(vector<int>& nums) {
        // 方法一 0-1 字典树
        int ans = 0;
        for (auto& num: nums) {
            ans = max(ans, max_xor(num));
            insert(num);
        }
        return ans;
    }

 
};