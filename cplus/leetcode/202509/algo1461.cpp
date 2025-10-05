#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 定长滑动窗口 1.3 其他（选做）
class Solution {
public:
    bool hasAllCodes(string s, int k) {
        // 自行解答
        if (s.length()<k) return false;
        set<int> codes;
        int val = 0;
        for (int i=0; i<k-1; ++i) val = (val<<1) + s[i] - '0';
        for (int i=k-1; i<s.length(); ++i) {
            val = (val<<1) + s[i] - '0';
            codes.insert(val);
            val &= (1 << (k-1)) - 1;
        }

        return codes.size() == 1 << k;  
    }
};