#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.8 相邻不同
class Solution {
public:
    int score(vector<string>& cards, char x) {
        // 自行解答 - 灵活运用题解方案
        int n = cards.size(), pair_cnt = 0, n0 = 0, n1 = 0, m0 = 0, m1 = 0;
        vector<vector<int>> cnt(2, vector<int>(10, 0));
        for (auto &c: cards) {
            int id0 = c[1] - 'a', id1 = c[0] - 'a';
            if (c[0] == x && c[1] == x) pair_cnt ++;
            else if (c[0] == x) {
                cnt[0][id0] ++; n0 ++;
                if (cnt[0][id0] > m0) m0 = cnt[0][id0];
            } else if (c[1] == x) {
                cnt[1][id1] ++;  n1 ++;
                if (cnt[1][id1] > m1) m1 = cnt[1][id1];
            }
        }
        int ans = 0;
        for (int i = 0; i<=pair_cnt; ++i) { // 枚举 card 字母都为 x 的数量的分布，归属第 1/2 个
            int val = min((n0+i)/2, n0+i- max(i,m0)) +
                 min((n1 + pair_cnt-i)/ 2, n1 + pair_cnt-i - max(pair_cnt-i,m1));
            ans = max(ans, val);
        }
        return ans;
    }
};