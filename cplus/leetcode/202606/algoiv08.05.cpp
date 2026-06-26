#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int multiply(int A, int B) {
        int ans = 0;
        for (int i=0; i<32; i++)
            if ((A >> i) & 1) ans += B << i;
        
        return ans;
    }
};