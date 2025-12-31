#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        // 自行解答
        const int mod = 1e9 + 7;
        unordered_map<int, int> y_cnt;
        for (auto & p : points) y_cnt[p[1]] ++;

        int ans = 0, i=1, n = points.size(); long long pre = 0;
        for (auto &[_, c] : y_cnt) {
            if (c > 1) {
                int comb = 1LL * c * (c-1) / 2 % mod;
                ans = (pre * comb + ans) % mod;
                pre = (pre + comb) % mod;
            }
        }
        return ans; 

    }

    int countTrapezoids2(vector<vector<int>>& points) {
        // 自行解答
        const int mod = 1e9 + 7;
        // 排序一定要要传入 vector<int>& ，否则需要创建数组，超时！！！
        sort(points.begin(), points.end(), [](vector<int>& a, vector<int>& b){
            return a[1] < b[1];
        });

        int ans = 0, i=1, n = points.size(); long long pre = 0;
        while (i < n) {
            int cnt = 1;
            while (i < n && points[i-1][1] == points[i][1]) {
                cnt ++; i++;
            }

            int comb =  1LL * cnt * (cnt-1) / 2 % mod;
            ans = (pre * comb + ans)  %  mod;
            pre = (pre + comb) % mod;
            i++;
        }
        return ans;   
    }    
};

