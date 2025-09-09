#include <bits/stdc++.h>
using namespace std;

// 位运算 - 其他
class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int ans = 0;
        for (int i=30; i>=0; --i) {
            auto l = (left>>i) & 1, r = (right>>i) & 1;

            if (l == r) 
                ans |= l << i;
            else break;
        }
        return ans;
    }
};

