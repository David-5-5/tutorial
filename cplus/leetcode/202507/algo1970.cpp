#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 7.2  并查集 - 进阶
class UnionFind {
    vector<int> fa;
    int row, col;
    unordered_map<int, set<int>> mp;
public:
    UnionFind(int n, int r, int c): fa(n), row(r), col(c) {
        ranges::iota(fa, 0);
    }

    int find(int x) {
        if (fa[x] != x) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }

    void merge(int from, int to) {
        int x = find(from), y = find(to);
        if (x != y) {
            fa[x] = y;
            if (mp.count(x)) mp[y].insert(mp[x].begin(), mp[x].end());
            else mp[y].insert(x%col);
            mp.erase(x);                    // 删除空集合
            mp[y].insert(y%col);
        }
    }
    
    bool is_fill(int x) {
        return mp[find(x)].size() == col;
    }
};


class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        // 自行解答，每天水域多一格，将水域的八个方向连接起来(阻断陆地)
        // 当水域的的元节点的列数量等于列数时，说明上下的陆地被完全阻断
        const int dirs[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
        vector<vector<int>> grid(row, vector<int>(col));
        UnionFind uf(row * col, row, col);   // 多出两个点，一个在最上面，一个在最下面
        
        int ans = 0;
        for (auto& cell : cells) {
            int i = cell[0]-1, j = cell[1]-1;
            grid[i][j] = 1;
            for (auto& dir : dirs) {
                int x = i + dir[0], y = j + dir[1];
                if (x >= 0 && x < row && y >= 0 && y < col && grid[x][y]) {
                    uf.merge(i * col + j, x * col + y);
                }
            }
            if (!uf.is_fill(i * col + j)) ans ++;
            else break;
        }
        return ans;
    }

};