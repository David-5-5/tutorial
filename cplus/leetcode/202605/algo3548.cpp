#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.7 分类讨论
class Solution {
    vector<vector<int>> rotate(vector<vector<int>> & a) {
        int m = a.size(), n = a[0].size();
        vector b(n, vector<int>(m));
        for (int i=0; i<m; ++i) for (int j=0; j<n; j++) {
            b[j][m-1-i] = a[i][j];  // b[j][i] = a[i][j]
        }
        return b;
    };
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        long long total = 0;
        for (auto &row : grid) for(auto &v : row) total += v;
        
        auto check = [&] (vector<vector<int>> a) -> bool {
            int m = a.size(), n = a[0].size();
            
            // 复用 top -> down, down -> top, 两个方向分别计算
            auto f = [&] () -> bool {
                // long long 保持一致性
                unordered_set<long long> x_set; x_set.insert(0); // 插入 0 表示不删除
                long long half = 0; // 前半部分和
                for (int i=0; i<m-1; i++) { // 至少非空两部分，因此必须留一行
                    for (int j=0; j<n; j++) {
                        half += a[i][j];
                        if (i > 0 || j ==0 || j == n-1) x_set.insert(a[i][j]);
                    }

                    if (n == 1) {
                        if (half * 2 == total || half * 2 - a[0][0] == total || half * 2 - a[i][0] == total) return true;
                        continue;
                    }
                    if (x_set.contains(half*2 - total)) return true;
                    if (i == 0) for (auto &v : a[i]) x_set.insert(v);
                }
                return false;
            };

            if (f()) return true;
            ranges::reverse(a); 
            return f();
        };

        return check(grid) || check(rotate(grid));

    }
};
int main() {
    vector<vector<int>> grid = {{1,4},{2,3}};
    cout << Solution().canPartitionGrid(grid);
}