#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  1.6 二维前缀和
class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();

        vector<vector<int>> prex(m+1, vector<int>(n+1));
        priority_queue<int, vector<int>, less<int>> max_heap;
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            prex[i+1][j+1] = matrix[i][j] ^ prex[i][j+1] ^ prex[i+1][j] ^ prex[i][j];
            max_heap.push(prex[i+1][j+1]);
        }

        for (int i=0; i<k-1; i++) {
            max_heap.pop();
        }

        return max_heap.top();
    }
};