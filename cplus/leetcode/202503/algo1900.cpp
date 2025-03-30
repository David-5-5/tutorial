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

    vector<int> earliestAndLatest2(int n, int firstPlayer, int secondPlayer) {
        // 自行解答，优化，状态压缩，但性能排序较低，仍有很大优化空间
        vector<int> memo(1<<n, -1);
        auto dfs = [&](this auto&& dfs, int mask) -> int {
            auto& res = memo[mask];
            if (res != -1) return res;
            vector<int> arr;
            for (int i=0; i<28; i++) {
                if ((mask>>i) & 1) arr.push_back(i+1);
            }
            int m = arr.size();
            if (m == 2) return res = 101;
            int mx = 0, mn = INT_MAX;
            
            int cnt = 1 << (m/2);
            for (int i=0; i<cnt; i++) {
                int nxt_mask = 0;
                for (int j=0; j<m/2; j++) {
                    
                    if (arr[j] == firstPlayer && arr[m-j-1] == secondPlayer) return res = 101;
                    if (arr[j] == firstPlayer || arr[m-j-1] == firstPlayer ) nxt_mask |= 1 << (firstPlayer-1);
                    else if (arr[j] == secondPlayer ||arr[m-j-1] == secondPlayer) nxt_mask |= 1 << (secondPlayer-1);
                    else if (i>>j & 1) nxt_mask |= 1 << (arr[m-j-1]-1);
                    else nxt_mask |= 1 << (arr[j]-1);
                }
                if (m%2) nxt_mask |= 1 <<(arr[m/2]-1);
                
                int val = memo[nxt_mask]!=-1?memo[nxt_mask]:dfs(nxt_mask);
                mx = max(mx, 1 + val % 100);
                mn = min(mn, 1 + val / 100);
            }
            return res = mn * 100 + mx;
        };

        int val = dfs((1<<n) - 1);
        return {val/100, val%100}; 
    }    

    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        // 进一步优化，但目前效果不理想
        vector<int> memo(1<<n, -1);

        auto dfs = [&](this auto&& dfs, int mask) -> int {
            
            auto& res = memo[mask];
            if (res != -1) return res;
            vector<int> arr;
            for (int i=0; i<28; i++) {
                if ((mask>>i) & 1) arr.push_back(i+1);
            }
            
            int m = arr.size();
            if (m == 2) return res = 101;
            int f = -1, s = -1;
            for (int i=0; i<m/2; i++) {
                if (arr[i] == firstPlayer && arr[m-i-1] == secondPlayer) return res = 101; 
                if (arr[i] == firstPlayer || arr[m-i-1] == firstPlayer) {
                    f = i;
                } 
                if (arr[i] == secondPlayer || arr[m-i-1] == secondPlayer) {
                    s = i;
                }
            }
            
            int mx = 0, mn = INT_MAX;
            
            vector<int> select; 
            for (int i=0; i<m; i++) {
                if (i!=f && i!=s && f!=m-i-1 && s!=m-i-1)
                    select.push_back(arr[i]);
            }
            m = select.size();
            int cnt = 1 << (m/2);
            // cout << m << "," << f << ", " << s << endl;
            for (int i=0; i<cnt; i++) {
                int nxt_mask = 1 << (firstPlayer-1) | 1 << (secondPlayer-1);
                for (int j=0; j<m/2; j++) {
                    if (i>>j & 1) nxt_mask |= 1 << (select[m-j-1]-1);
                    else nxt_mask |= 1 << (select[j]-1);
                }
                if (m%2) nxt_mask |= 1 <<(select[m/2]-1);
                
                int val = memo[nxt_mask]!=-1?memo[nxt_mask]:dfs(nxt_mask);
                mx = max(mx, 1 + val % 100);
                mn = min(mn, 1 + val / 100);
            }
            return res = mn * 100 + mx;
        };

        int val = dfs((1<<n) - 1);
        return {val/100, val%100};    
    }       
};