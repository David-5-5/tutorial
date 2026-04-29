#include <bits/stdc++.h>
using namespace std;

// 顺序
class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.length(), lim0 = sqrt(n), ans = 0;
        
        deque<int> inx0;
        for (int i=0; i<n; i++) if (s[i] == '0') inx0.push_back(i);
        inx0.push_back(n);  // 增加哨兵

        for (int l=0; l<n; l++) {
            if (inx0.front() < l) inx0.pop_front();
            int prev = l-1;
            for (int j = 0; j<min((int)inx0.size(), lim0); j++) {
                auto cnt1 = (prev - l + 1) - j;
                ans += cnt1 - j * j>=0?inx0[0]-prev:max(0, inx0[j]-prev+cnt1 - j * j);
                prev = inx0[j];
            }
        }
        return ans;        
    }
};