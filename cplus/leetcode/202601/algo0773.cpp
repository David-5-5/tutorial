#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.3 图论建模 + BFS 最短路
class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        // 自行解答
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        int target = 5 << 12 | 4 << 9 | 3 << 6 | 2 << 3 | 1;
        int m = 2, n = 3, source = 0;
        for (int r=0; r<m; ++r) for (int c=0; c<n; ++c) {
            source |= board[r][c] << (r*n + c) * 3;
        }
        
        vector<int> q = {source}; set<int> vis = {source}; int step = 0; 
        while (!q.empty()) {
            vector<int> nxt;
            for (auto& u: q) {
                if (u == target) return step;
                int r = 0, c = 0;
                for (int i = 0; i<6; i++) if (((u >> (i * 3)) & 7) == 0) {
                    r = i / 3, c = i % 3; break;
                }
                for (int i=0; i<4; i++) {
                    auto v = u;
                    int nr = r + dirs[i][0], nc = c + dirs[i][1];
                    if (nr>=0 && nr <m && nc>=0 && nc<n) {
                        int val = (v >> (nr * n + nc) * 3) & 7;
                        v ^= val << (nr * n + nc) * 3; 
                        v |= val << (r * n + c) * 3;

                        if (vis.insert(v).second) nxt.push_back(v);
                    }
                }
            }

            q = move(nxt); step ++;
        }

        return -1;      
    }
};

int main() {
    vector<vector<int>> board = {{1,2,3},{4,0,5}};
    cout << Solution().slidingPuzzle(board) << endl;
}