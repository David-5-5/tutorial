#include <bits/stdc++.h>
using namespace std;

// 二、网格图 BFS
class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        // 参考题解，题目看错了
        int n = board.size(); vector<bool> vis(n*n+1);
        auto coor = [&](int pos) -> pair<int, int> {
            int r = n - 1 - (pos - 1) / n;
            int c = (n-r)%2 ? (pos - 1) % n : n - 1 - (pos - 1) % n;
            return {r, c};
        };
        vector<int> q;
        int dest = n * n;
        q.emplace_back(1); vis[1] = true; int dis = 0;
        while (!q.empty()) {
            vector<int> nxt;
            for (auto& u: q) {
                if (u == dest) return dis;
                for (int i=1; i<=6; ++i) {
                    int v = u + i; if (v > dest) break;
                    auto pos = coor(v);
                    if (board[pos.first][pos.second] > 0) {
                        v = board[pos.first][pos.second];
                    } 
                    if (!vis[v]) {
                        vis[v] = true;
                        nxt.emplace_back(v);
                    }
                }
            }
            q = move(nxt); dis++;
        }

        return -1;
    }
};

int main() {
    // vector<vector<int>> board = {{-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1},
    //     {-1,-1,-1,-1,-1,-1},{-1,35,-1,-1,13,-1},{-1,-1,-1,-1,-1,-1},{-1,15,-1,-1,-1,-1}};
    vector<vector<int>> board =   { {-1,7,-1},{-1,6,9},{-1,-1,2}};
    cout << Solution().snakesAndLadders(board) << endl;
}