#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.7 搜索
struct Move {
    int x0, y0; // 起点
    int dx, dy; // 方向
    int step;
};

class Solution {
    vector<pair<int, int>> DIRS = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    unordered_map<string, vector<pair<int, int>>> piece_dir = {
        {"rook", {DIRS.begin(), DIRS.begin() + 4}},
        {"bishop", {DIRS.begin()+4, DIRS.end()}},
        {"queen", DIRS}
    };

    // 计算位于 (x0,y0) 的棋子在 dirs 这些方向上的所有合法移动
    vector<Move> generate_moves(int x0, int y0, vector<pair<int, int>>& dirs) {
        const int SIZE = 8;
        vector<Move> moves = {{x0, y0, 0, 0, 0}};
        for (auto& [dx, dy]: dirs) {
            int x = x0 + dx, y = y0 + dy;
            for (int step=1; x>0 && x<=SIZE && y>0 && y<=SIZE; step++) {
                moves.emplace_back(x0, y0, dx, dy, step);
                x += dx; y += dy;
            }
        }
        return moves;
    };

    bool is_valid(Move& m1, Move& m2) {
        auto x1 = m1.x0, y1=m1.y0, x2 = m2.x0, y2=m2.y0;
        for (int i=0; i<max(m1.step, m2.step); ++i) {
            if (i < m1.step) x1 += m1.dx, y1 += m1.dy;
            if (i < m2.step) x2 += m2.dx, y2 += m2.dy;
            if (x1 == x2 && y1 == y2) return false;
        }
        return true;
    };

public:
    int countCombinations(vector<string>& pieces, vector<vector<int>>& positions) {
        int n = pieces.size();

        vector<vector<Move>> all_moves;
        for (int i=0; i<n; ++i) {
            all_moves.push_back(generate_moves(positions[i][0], positions[i][1], piece_dir[pieces[i]]));
        }

        vector<Move> path(n); int ans = 0; 
        auto dfs = [&](this auto&& dfs, int i) -> void {
            if (i == n) {ans ++; return;} 
            
            for (auto & m: all_moves[i]) {
                bool  ok = true;
                for (int j=0; j<i; ++j)
                    if (!is_valid(m, path[j])) {ok=false; break;}
                if (ok) {path[i]=m; dfs(i+1);}
            }
        };

        dfs(0); return ans;
    }
};