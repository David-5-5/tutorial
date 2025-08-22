#include <bits/stdc++.h>
using namespace std;

// 位运算 - 基础题
class Solution {
public:
    int binaryGap(int n) {
        // 自行解答
        int last = -1, ans = 0;
        for (int i=0; i<32; ++i) {
            if (n >> i & 1) {   
                if(last!=-1) ans = max(ans, i-last);
                last = i;
            }
        }
        return ans;
    }

    int binaryGap(int n) {
        // 自行解答
        int last = -1, ans = 0, i = 0;
        while (n) {
            if (n & 1) {   
                if(last!=-1) ans = max(ans, i-last);
                last = i;
            }
            i++; n>>=1;
        }
        return ans;
    }    
};