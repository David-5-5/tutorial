#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 其他
class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        // 自行解答，不需要质因子分解
        // 质因子分解的组合数还挺复杂
        int n = arr.size(), mod = 1e9 + 7;
        sort(arr.begin(), arr.end());
        unordered_map<int,int> hash;
        for (int i=0; i<n; ++i) hash[arr[i]] = i;
        
        unordered_map<int, int> memo;
        auto dfs = [&](this auto&& dfs, int i) -> int {

            int res = 1;
            if (memo.count(i)) return memo[i];
            for (int j=0; j<i; j++) {
                if (arr[i] % arr[j] == 0 && hash.count(arr[i] / arr[j])) {
                    res = (res + (long) dfs(j) *  dfs(hash[arr[i] / arr[j]])) % mod;
                }
            }
            return memo[i] = res;
        };
        
        int ans = 0;
        for (int i=0; i<n; i++) ans = (ans + dfs(i)) % mod;

        return ans;
    }


};