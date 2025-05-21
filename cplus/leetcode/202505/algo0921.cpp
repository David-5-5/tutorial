#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.4 合法括号字符串
class Solution {
public:
    int minAddToMakeValid(string s) {
        // 自行解答
        int left = 0, ans = 0;

        for (auto& ch : s) {
            if (ch == '(') left += 1;
            else left?left -- : ans++;
        }
        return ans + left;
    }
};