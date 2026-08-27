#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<double> sampleStats(vector<int>& count) {
        vector<double> ans(5);
        long long sum = 0, cnt = 0, mx_cnt = 0;
        ans[0] = INT_MAX, ans[1] = INT_MIN;
        deque<pair<int, int>> val_cnt;
        for (int i=0; i<256; i++) {
            if (count[i]) {
                ans[0] = min(ans[0], 1.0 * i);
                ans[1] = max(ans[1], 1.0 * i);
                if (count[i] > mx_cnt) {
                    ans[4] = i; mx_cnt = count[i];
                }
                sum += 1LL * i * count[i]; cnt += count[i];
                val_cnt.emplace_back(i, cnt);
            }
        }
        ans[2] = 1.0 * sum / cnt;

        while (val_cnt.front().second < (cnt+1) / 2) {
            val_cnt.pop_front();
        }
        
        ans[3] = 1.0 * val_cnt.front().first; 

        if (cnt % 2 == 0 && val_cnt.front().second == cnt/2 ) {
            val_cnt.pop_front();
            ans[3] += val_cnt.front().first; ans[3] /= 2;
        }

        return ans;
    }
};