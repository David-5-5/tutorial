#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.7 分类讨论
class Solution {
public:
    int minOperations(string s) {
        // 若不给出测试案例，很难将各种情况考虑完整。
        if (s.length() == 1) return 0;
        if (s.length() == 2) return s[0] <= s[1]?0:-1;
        string t = s; int n = t.length(), res1 = 0, res2 = 0;
        sort(t.begin(), t.end()-1);
        for (int i=0; i<n-1; i++) {
            if (t[i] != s[i]) {
                res1 ++;  break;
            }
        }
        if (t[n-2] > t[n-1]) {
            sort(t.begin()+1, t.end());
            res1 ++;
            if (t[0] > t[1]) res1 ++;
        }
        
        t = s; sort(t.begin() + 1, t.end());
        for (int i=1; i<n; i++) {
            if (t[i] != s[i]) {
                res2 ++;  break;
            }
        }
        if (t[0] > t[1]) {
            sort(t.begin(), t.end()-1);
            res2 ++;
            if (t[n-2] > t[n-1]) res2 ++;
        }

        return min(res1, res2);
    }


};