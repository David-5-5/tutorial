#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countCompleteDayPairs(vector<int>& hours) {
        // 自行解答
        unordered_map<int, int> h_cnt;
        long long ans = 0;
        for (auto h: hours) {
            h %= 24;
            ans += h_cnt[(24 - h)%24];
            h_cnt[h] ++;
        }

        return ans;
    }
};