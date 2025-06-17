#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.4 堆 - 第 K 小/大
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        // 自行解答
        int n = matrix.size(), m = matrix[0].size();
        vector vis(n, vector<bool>(m));
        
        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;

        pq.emplace(matrix[0][0], 0, 0);
        vis[0][0] = true;

        for (int _=0; _<k-1; ++_) {
            auto [_, x, y] = pq.top(); pq.pop();
            
            if (x+1<n && !vis[x+1][y]) {
                pq.emplace(matrix[x+1][y], x+1, y);vis[x+1][y] = true;
            }
            if (y+1<m && !vis[x][y+1]) {
                pq.emplace(matrix[x][y+1], x, y+1);vis[x][y+1]= true;
            }
        }

        return get<0>(pq.top());

    }

    int kthSmallest2(vector<vector<int>>& matrix, int k) {
        // 自行解答
        int n = matrix.size(), m = matrix[0].size();
        if (n == 1) return matrix[0][k-1];
        if (m == 1) return matrix[k-1][0];
        
        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;

        for (int i=0; i<n; i++)
            pq.emplace(matrix[i][0], i, 0);

        for (int _=0; _<k-1; ++_) {
            auto [_, r, c] = pq.top(); pq.pop();
            
            if (c+1<m) 
                pq.emplace(matrix[r][c+1], r, c+1);
        }

        return get<0>(pq.top());
    }    
};