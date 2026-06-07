#include <bits/stdc++.h>
using namespace std;

// 七、其他线性 DP - 7.6 多维 DP
class Solution {
public:
    int countCoprime(vector<vector<int>>& mat) {
        // 自行解答 暴力 gcd 的数量指数下降
        const int mod = 1e9 + 7;
        unordered_map<int, int> cnt;
        int n = mat.size(), m = mat[0].size();
        for (int j=0; j<m; j++) cnt[mat[0][j]] ++;
        
        for (int i=1; i<n; i++) {
            unordered_map<int, int> nxt;
            for (int j=0; j<m; j++) {
                for (auto &[k, v]: cnt) 
                    nxt[gcd(k, mat[i][j])] = (nxt[gcd(k, mat[i][j])] + v) % mod;
            }

            cnt = move(nxt);
        }
        return cnt[1];
    }

    int countCoprime2(vector<vector<int>>& mat) {
        // 自行解答 暴力 gcd 的数量指数下降
        const int mod = 1e9 + 7;
        vector<int> cnt(151, 0);
        int n = mat.size(), m = mat[0].size();
        for (int j=0; j<m; j++) cnt[mat[0][j]] ++;
        
        for (int i=1; i<n; i++) {
            vector<int> nxt(151, 0);

            for (int g=1; g<=150; g++) {
                if (cnt[g] == 0) continue;
                for (int j=0; j<m; j++) 
                        nxt[gcd(g, mat[i][j])] = (nxt[gcd(g, mat[i][j])] + cnt[g]) % mod;
            }

            cnt = move(nxt);
        }
        return cnt[1];
    }    
};