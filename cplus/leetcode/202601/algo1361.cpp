#include <bits/stdc++.h>
using namespace std;

// 图论算法 二、拓扑排序 2.1 拓扑排序
class Solution {
public:
    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
        // 自行解答 toplogy sort 
        vector<int> degree(n);
        for (int i=0; i<n; ++i) {
            if (leftChild[i]!=-1) degree[leftChild[i]] ++;
            if (rightChild[i]!=-1) degree[rightChild[i]] ++;
        }

        int root = -1;
        for (int i=0; i<n; ++i) {
            if (degree[i] > 1) return false;    // 每棵树只有一个父节点，degree == 1
            if (degree[i] == 0) 
                if (root == -1) root=i;         // 根节点只有一个 degree == 0 的节点只有一个
                else return false;
        }

        if (root == -1) return false;           // 必须存在根节点
        int cnt = 1; vector<int> q = {root};    // 从根节点必须遍历所有节点
        while (!q.empty()) {
            vector<int> nxt;
            for (auto& i: q) {
                if (leftChild[i]!=-1) {
                    degree[leftChild[i]]--;
                    if (degree[leftChild[i]] == 0) {
                        nxt.emplace_back(leftChild[i]); cnt++;
                    };
                }
                if (rightChild[i]!=-1) {
                    degree[rightChild[i]]--;
                    if (degree[rightChild[i]] == 0) {
                        nxt.emplace_back(rightChild[i]); cnt++;
                    };                           
                }
            }
            q = move(nxt);                      
        }

        return cnt == n;
    }
};