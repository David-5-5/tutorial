#include <bits/stdc++.h>
using namespace std;

// 双周赛 141
class Solution {
public:
    int maxRemovals(string source, string pattern, vector<int>& targetIndices) {
        // 自行解答， 超时
        int n = source.size(), m = pattern.size();
        auto check = [&](set<int> del) -> bool {
            int j = 0;
            for (int i=0; i<n; i++) {
                if (del.count(i)) continue;
                if (source[i] == pattern[j]) j++;
                if (j == m) break;
            }
            if (m == j) return true;
            else return false;
        };

        int k = targetIndices.size();
        function<int(int, set<int>)> dfs = [&](int i, set<int> del) -> int{
            if (i == k) 
                return del.size();
            
            // select to del
            int cnt = dfs(i+1, del);

            del.emplace(targetIndices[i]);
            if (check(del)) cnt = max(cnt, dfs(i+1, del));
            del.erase(targetIndices[i]);

            return cnt;
        };

        set<int> del;
        return dfs(0, del);   
    }

    int maxRemovals(string source, string pattern, vector<int>& targetIndices) {
        // 参考题解，LIS 在 dfs 之中判断
        int n = source.size(), m = pattern.size();
        set<int> indice(targetIndices.begin(), targetIndices.end());


        vector<vector<int>> memo(n, vector<int>(m + 1, -1)); // 
        int k = targetIndices.size();
        function<int(int, int)> dfs = [&](int i, int j) -> int{
            if (i < j) return INT_MIN;  // !! 边界条件
            if (i < 0) return 0;
            
            int&  res= memo[i][j+1]; // 当 j == -1 表示 pattern 全匹配
            if (res != -1) return res;
            
            res = dfs(i-1, j) + indice.count(i); // 后续的 i+1 个 source中的的字符都可以删除了
            if (j >= 0 && source[i] == pattern[j]) res = max(res, dfs(i-1,j-1));

            return res;
        };

        return dfs(n-1, m-1);  
    }    
};