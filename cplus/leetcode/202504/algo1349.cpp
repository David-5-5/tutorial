#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.4 子集状压 DP
class Solution {
public:
    int maxStudents(vector<vector<char>>& seats) {
        // 自行解答 记忆化搜索 参见python
        int m = seats.size(), n = seats[0].size();
        
        unordered_map<int, int> memo;
        auto dfs = [&](this auto&& dfs, int top, int left, int pos) -> int {
            if (pos == m * n) return 0;
            
            int mask = top << 16 | left << 8 | pos;
            if (memo.count(mask)) return memo[mask];
            
            // Not sit
            int res = (pos+1)%n?dfs(top, left, pos + 1): dfs(left, 0, pos + 1);
            
            // Try to sit
            int x = pos / n, y = pos % n;
            auto can_site = (seats[x][y] == '.') 
                && !(y > 0 && (top & (1 << (y - 1)))) 
                && !(y < n - 1 && (top & (1 << (y + 1))))  
                && !(y > 0 && (left & (1 << (y - 1))));
            
            if (can_site) {
                int new_left = left | (1 << (pos % n));                
                res = max(res, 1 + ((pos+1)%n?dfs(top, new_left, pos + 1): dfs(new_left, 0, pos + 1)));
            }
            
            return memo[mask] = res;
        };
        
        return dfs(0, 0, 0);
    }

};