#include <bits/stdc++.h>
using namespace std;

// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
    
    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

// 二叉树 - 2.15 N 叉树
class Solution {
public:
    Node* construct(vector<vector<int>>& grid) {
        // 自行解答
        bool isLeaf = true;
        int n = grid.size();
        for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) {
            if (grid[i][j] != grid[0][0]) {
                isLeaf = false; break;
            }
        }
        if (isLeaf) return new Node(grid[0][0], isLeaf);
        else {
            vector<vector<int>> tl(n/2, vector<int>(n/2)), tr(n/2, vector<int>(n/2)),
                bl(n/2, vector<int>(n/2)), br(n/2, vector<int>(n/2));
            for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) {
                if (i < n/2 && j < n/2) {
                    tl[i][j] = grid[i][j];
                } else if (i<n/2 && j >=n/2) {
                    tr[i][j-n/2] = grid[i][j];
                } else if (i>=n/2 && j<n/2) {
                    bl[i-n/2][j] = grid[i][j];
                } else br[i-n/2][j-n/2] = grid[i][j];
            }
            return new Node(grid[0][0], isLeaf, construct(tl), construct(tr), construct(bl), construct(br));
        }
    }
};