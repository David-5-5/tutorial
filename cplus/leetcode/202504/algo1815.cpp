#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.5 其他状压 DP
class Solution {
public:
    int maxHappyGroups(int batchSize, vector<int>& groups) {
        // 自行解答 
        int cnt[batchSize], n =  groups.size();
        memset(cnt, 0, sizeof(cnt));
        for (auto& v : groups) cnt[v%batchSize] ++;
    
        unordered_map<long, int> memo;
        auto dfs = [&](this auto&& dfs, int i, int l, long s) -> int {
            if (i == n) return 0;

            long mask = (long)i << 60 | (long)l << 56 | s;
            if (memo.count(mask)) return memo[mask];

            int res = 0;
            for (int k=0; k<batchSize; ++k) {
                int c = (s >> (5*k)) & 31;
                if (c) {
                    // cout << (s&(tot1^(c-1)<<(5*k)))) << endl;
                    res = max(res, dfs(i+1, (l+k)%batchSize, s-((long)1<<(5*k))));
                }
            }
            return memo[mask] = res + (l==0);
        };

        long s = 0;
        for (int i=batchSize-1; i>=0; --i) {
            s = s << 5 | cnt[i];    // 
        }
        
        return dfs(0, 0, s);  

    }


};