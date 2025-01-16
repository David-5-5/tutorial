#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 逆向思维
// 参考题解，广度优先搜索 或 深度优先搜索
class Solution {
    
public:
    const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<vector<int>> heights;
    void dfs(int row, int col, vector<vector<bool>>& ocean) {
        if (ocean[row][col]) return;
        int m = heights.size(), n = heights[0].size();
        ocean[row][col] = true;
        for (int i=0; i<4; i++) {
            int nr = row + dirs[i][0], nc = col + dirs[i][1];
            if (nr>=0 && nr <m && nc>=0 && nc<n &&
             !ocean[nr][nc] && heights[nr][nc] > heights[row][col])
                dfs(nr, nc, ocean);
        }

    }

    void bfs(int row, int col, vector<vector<bool>>& ocean) {
        int m = heights.size(), n = heights[0].size();
        
        ocean[row][col] = true;
        queue<pair<int, int>> qu;
        qu.emplace(row, col);

        while (!qu.empty()){
            auto [row, col] = qu.front();
            qu.pop();

            for (int i=0; i<4; i++) {
                int nr = row + dirs[i][0], nc = col + dirs[i][1];
                if (nr>=0 && nr <m && nc>=0 && nc<n &&
                    !ocean[nr][nc] && heights[nr][nc] > heights[row][col]){
                    ocean[nr][nc] = true;
                    qu.emplace(nr, nc);
                }
            }
        }

    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        this->heights = heights;
        int m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pacific;
        vector<vector<bool>> altantic;
        pacific.assign(m, vector<bool>(n));
        altantic.assign(m, vector<bool>(n));

        for (int i=0; i<n; i++) {
            dfs(0, i, pacific);
            dfs(m-1, i, altantic);
            // bfs(0, i, pacific);
            // bfs(m-1, i, altantic);
        }

        for (int i=0; i<m; i++) {
            dfs(i, 0, pacific);
            dfs(i, n-1, altantic);
            // bfs(i, 0, pacific);
            // bfs(i, n-1, altantic);
        }
        vector<vector<int>> ans;
        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                if (pacific[i][j] && altantic[i][j])
                    ans.push_back({i, j});
            }   
        }
        return ans;
    }
};

int main() {
    vector<vector<int>> heights = {{1,2,2,3,5},{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5},{5,1,1,2,4}};
    Solution().pacificAtlantic(heights);
    return 0;
}