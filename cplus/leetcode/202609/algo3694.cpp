#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int distinctPoints(string s, int k) {
        // 滑动窗口
        set<pair<int, int>> terms;

        int x = 0, y = 0, n = s.length();
        for (auto& c: s) {
            if (c == 'U') y ++;
            else if (c == 'D') y--;
            else if (c == 'L') x--;
            else x ++;
        }

        int dx = 0, dy = 0;
        for (int i=0; i<k; i++){
            auto & c = s[i];
            if (c == 'U') dy ++;
            else if (c == 'D') dy--;
            else if (c == 'L') dx--;
            else dx ++;
        }

        terms.emplace(x-dx, y-dy);

        for (int i=k; i<n; i++) {
            auto & prev = s[i-k];
            if (prev == 'U') dy --;
            else if (prev == 'D') dy++;
            else if (prev == 'L') dx++;
            else dx --;
            auto & c = s[i];
            if (c == 'U') dy ++;
            else if (c == 'D') dy--;
            else if (c == 'L') dx--;
            else dx ++;
            terms.emplace(x-dx, y-dy);         
        }

        return terms.size();
    }


};