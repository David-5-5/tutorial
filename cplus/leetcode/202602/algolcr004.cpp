#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        // 同 137 题
        int a = 0, b = 0;
        for (auto val: nums) {
            b = ~a & (b ^ val);
            a = ~b & (a ^ val);
        }
        return b;     
    }
};