#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> drawLine(int length, int w, int x1, int x2, int y) {
        vector<int> ans(length); 
        
        for (int i=x1; i<=x2; i++) {
            auto inx = (y * w + i) >> 5;
            ans[inx] |= 1 << (31 - i%32);
        }

        return ans;    
    }
};