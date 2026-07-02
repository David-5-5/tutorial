#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool patternMatching(string pattern, string value) {
        // 边界条件 sa != sb value.size() == 0 pattern.size() == 0
        //         cnt_a = 0 cnt_b = 0
        if (pattern.size() == 0) return value.size() == 0;
        int cnt_a = 0, cnt_b = 0, n = value.size();

        for (auto & p : pattern)
            if (p == 'a') cnt_a ++;
            else cnt_b ++;
        if (value.size() == 0) return cnt_a ^ cnt_b;
        
        auto check = [&](int a, int b) -> bool {
            string sa = "", sb = ""; int i = 0;
            for (auto p : pattern) {
                if (p == 'a') {
                    if (a == 0) continue;
                    if (sa == "") sa = value.substr(i, a);
                    else if (sa != value.substr(i, a)) return false;
                    i += a;
                } else {
                    if (b == 0) continue;
                    if (sb == "") sb = value.substr(i, b);
                    else if (sb != value.substr(i, b)) return false;
                    i += b;
                }
            }
            return sa != sb;
        };
        
        if (cnt_a == 0) return (n % cnt_b == 0) && check(0, n / cnt_b);
        if (cnt_b == 0) return (n % cnt_a == 0) && check(n / cnt_a , 0);

        for (int a = 0; a<= n/cnt_a; a++) {
            if ((n- cnt_a * a) % cnt_b) continue;
            auto b = (n- cnt_a * a) / cnt_b;

            if (check(a, b)) return true;
        }

        return false;
    }
};