#include <bits/stdc++.h>
using namespace std;
// 付费油漆墙 + 免费墙 = n
// 付费墙 + 付费墙的时间 >= n
// 1 + ... + 1 + time[i1] + ... + time[ij] >= n
// 转化为 (time[i1] + 1) + ... + (time[ij] + 1) >= n 情况下 cost(i1) + ... + cost(ij) 最小化
// 至少型 0-1 背包

class Solution {
public:
    // 套用 0-1 背包(降维)递推公式
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int n = time.size();
        vector<int> f(n+1, INT_MAX / 2);
        f[0] = 0;
        for (int i=0; i<n; i++) {    
            for (int l=n; l; l--) {
                f[l] = min(f[l], f[max(l-time[i]-1,0)] + cost[i]);
            }
        }
        return f[n];
    };

    // dfs 递归
    int paintWalls2(vector<int>& cost, vector<int>& time) {
        int n = time.size();
        vector<vector<int>> memo(n, vector<int>(n+1, -1));
        
        // 内置函数写法 1
        function<int(int, int)> dfs = [&](int i, long j){

            if (j<=0) return 0;
            if (i<0) return INT_MAX / 2;

            int& res = memo[i][j];
            if (res!=-1) return res;

            return res = min(dfs(i-1,j), dfs(i-1, j-time[i]-1)+cost[i]);
            
        };
        // return dfs(n-1, n);

        // 内置函数写法 2
        auto dfs2 = [&](auto&& dfs2, int i, long j)-> int{

            if (j<=0) return 0;
            if (i<0) return INT_MAX / 2;

            int& res = memo[i][j];
            if (res!=-1) return res;

            return res = min(dfs2(dfs2, i-1,j), dfs2(dfs2,i-1, j-time[i]-1)+cost[i]);
            
        };
        
        return dfs2(dfs2, n-1, n);
        
    };
};

int main() {
    Solution sol;
    vector<int> cost = {2,3,4,2};
    vector<int> time = {1,1,1,1};
    cout << sol.paintWalls(cost, time) << endl;
    cout << sol.paintWalls2(cost, time) << endl;
}