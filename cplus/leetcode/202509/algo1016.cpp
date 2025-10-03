#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 定长滑动窗口 1.2 进阶
class Solution {
public:
    bool queryString(string s, int n) {
        // 参考题解 脑筋急转弯
        for (int i=1; i<=n; ++i) {
            auto bin = bitset<32>(i).to_string();
            if (s.find(bin.substr(bin.find('1'))) == string::npos) return false;
        }
        return true;
    }
};