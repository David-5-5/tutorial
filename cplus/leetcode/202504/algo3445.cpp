#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.5 其他一维前缀和
class Solution {
public:
    int maxDifference(string s, int k) {
        int n = s.size();
        vector<vector<int>> pres(5, vector<int>(n+1));

        for(int i=0; i<n; ++i) {
            int v = s[i] - '0';
            for (int j=0; j<5; ++j) {
                if (j==v) pres[j][i+1] = pres[j][i] + 1;
                else pres[j][i+1] = pres[j][i];
            }
        }

        int ans = INT_MIN;
        for (int a=0; a<5; ++a) for (int b=0; b<5; ++b) {
            vector<deque<pair<int,int>>> queue(4, deque<pair<int,int>>());
            if (a == b) continue;
            for (int i=1; i<=n; i++) {
                int val = pres[a][i] - pres[b][i];

                int cur = (pres[a][i]%2 << 1) + (pres[b][i] % 2);
                int prev = (1 ^ pres[a][i]%2 << 1) + (pres[b][i] % 2);

                while ()

            }
    
        }

    }
};