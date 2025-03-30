#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        // 自行解答，超时
        vector<int> arr(n);
        for (int i=1; i<=n; ++i) arr[i] = i;    // 忘了用状态压缩了

        // arr 需要状态压缩
        auto dfs = [&](this auto&& dfs, vector<int> arr) -> vector<int> {
            int m = arr.size();
            if (m == 2) return {1, 1};
            int mx = 0, mn = INT_MAX;
            vector<int> nxt;
            int cnt = 1 << (m/2);
            for (int i=0; i<cnt; i++) {
                for (int j=0; j<m/2; j++) {
                    if (arr[j] == firstPlayer && arr[n-j-1] == secondPlayer) return {1,1};
                    
                    if (arr[j] == firstPlayer) nxt.push_back(firstPlayer);
                    else if (arr[n-j-1] == secondPlayer nxt.push_back(secondPlayer));
                    else if (i>>j & 1) nxt.push_back(arr[n-j-1]);
                    else nxt.pop_back(arr[j]);
                }
                if (m%2) nxt.push_back(arr[m/2]);
                sort(nxt.begin(), nxt.end());
                int val = dfs(nxt);
                mx = max(mx, 1 + val);
                mn = min(mn, 1 + val);
            }
            return {mn, mx};
        };

        return dfs(arr);

    }
};