#include <bits/stdc++.h>
using namespace std;

// 周赛 
class Solution {
public:
    vector<bool> canMakePalindromeQueries(string s, vector<vector<int>>& queries) {
        int n, half = s.length(), s.length() >> 1;
        string t = s.substr(half, half).reserve();
        s = s.substr(0, half);

        vector<vector<int>> pres_s;
        vector<vector<int>> pres_t;
        pres_s.assign(half+1, vector<int>(26));
        pres_t.assign(half+1, vector<int>(26));

        vector<int> pres_d(half+1);

        // 初始化 pres_s
        for (int i=0; i<half; i++) {
            for (int j= 0; j<26; j++) {
                pres_s[i+1][j] = pres_s[i][j] + (int(s[i]) == int('a') + j)
            }
        }

        // 初始化 pres_t
        for (int i=0; i<half; i++) {
            for (int j= 0; j<26; j++) {
                pres_t[i+1][j] = pres_t[i][j] + (int(t[i]) == int('a') + j)
            }
        }

        // 初始化 pres_d
        for (int i=0; i<half; i++) {
            pres_d[i+1] = pres[i] + (s[i]!=t[i])
        }

        vector<bool> ans(queries.size());
        

    }
};