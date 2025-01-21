#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 等价转换
class Solution {
public:
    int minChanges(string s) {
        // 自行解答，两两比较即可
        int ans = 0;
        for (int i=0; i<s.size(); i+=2)
            if (s[i] != s[i+1]) ans ++;
        
        return ans;
    }
};