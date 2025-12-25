#include <bits/stdc++.h>
using namespace std;

// 网格图 五、综合应用
class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        // 参考题解，看了题解后，这题还是可以做的，本质上就是 BFS 求最短路径
        // 就是 BFS 的状态参数有些多了 (x, y, e, U) x, y是坐标，e为当前能力 U 为垃圾的状压集合
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int sx = 0, sy = 0, cnt_l = 0, m = classroom.size(), n = classroom[0].size();
        vector l_state(m, vector(n, 0));  // 记录 L 压缩状态
        for (int i=0; i<m; i++) for (int j=0; j<n; j++) {
            auto ch = classroom[i][j];
            if (ch == 'S') sx = i, sy = j;
            else if (ch == 'L') l_state[i][j] = 1 << (cnt_l++);
        }

        vector vis(m, vector(n, vector(energy+1, vector<bool>(1 << cnt_l))));
        vector<tuple<int, int, int, int>> q; int step = 0;
        q.emplace_back(sx, sy, energy, 0); vis[sx][sy][energy][0] = true;
        
        while (!q.empty()) {
            vector<tuple<int, int, int, int>> nxt;
            for (auto &[x, y, e, U] : q) {
                if (U + 1 == 1 << cnt_l)  return step;
                if (e == 0) continue; 
                // 向 4 个方向移动
                for (auto & [dx, dy]: dirs) {
                    int nx = x + dx, ny = y + dy;
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && classroom[nx][ny] != 'X') {
                        int new_e = classroom[nx][ny] == 'R' ? energy:e-1;
                        int new_U = U | l_state[nx][ny];
                        if (vis[nx][ny][new_e][new_U]) continue;
                        vis[nx][ny][new_e][new_U] = true;
                        nxt.emplace_back(nx, ny, new_e, new_U);
                    }
                }
            }
            q = move(nxt); step++;
        }   
        return -1;

    }
};