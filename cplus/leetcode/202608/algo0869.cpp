#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool reorderedPowerOf2(int n) {
        set<string> pow2s; int pow2 = 1;
        for (int _=0; _<30; _++) {
            string powstr = to_string(pow2); ranges::sort(powstr);
            pow2s.insert(powstr);
            pow2 *= 2;
        }
        
        string sn = to_string(n); ranges::sort(sn);
        return pow2s.count(sn);
    }
};