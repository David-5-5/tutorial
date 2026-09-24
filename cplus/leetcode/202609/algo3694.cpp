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

    int distinctPoints2(string s, int k) {
        set<pair<int, int>> terms;

        auto change = [&](char& ch, bool inc, int& x, int& y) -> void{
            if (ch == 'U') y += inc?1:-1;
            else if (ch == 'D') y += inc?-1:1;
            else if (ch == 'L') x += inc?-1:1;
            else x += inc?1:-1;
        };

        int x = 0, y = 0, n = s.length();
        for (auto& c: s) {
            change(c, true, x, y);
        }

        int dx = 0, dy = 0;
        for (int i=0; i<k; i++){
            change(s[i], true, dx, dy);
        }

        terms.emplace(x-dx, y-dy);

        for (int i=k; i<n; i++) {
            change(s[i-k], false, dx, dy);
            change(s[i], true, dx, dy);    
            terms.emplace(x-dx, y-dy);    
        }

        return terms.size();        
    }

    int distinctPoints3(string s, int k) {
        set<pair<int, int>> terms;

        auto change = [&](char& ch, bool inc, int& x, int& y) -> void{
            if (ch == 'U') y += inc?1:-1;
            else if (ch == 'D') y += inc?-1:1;
            else if (ch == 'L') x += inc?-1:1;
            else x += inc?1:-1;
        };

        int x = 0, y = 0, n = s.length();

        terms.emplace(0, 0);

        for (int i=k; i<n; i++) {
            change(s[i-k], false, x, y);
            change(s[i], true, x, y);    
            terms.emplace(x, y);    
        }

        return terms.size();        
    }

};