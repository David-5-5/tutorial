#include <bits/stdc++.h>
using namespace std;

// 位运算 - 思维题 - 贪心、脑筋急转弯等
class Solution {
public:
    bool makeStringsEqual(string s, string target) {
        // 自行解答 - 如果 s 中存在 1,可以转换为除全 0 的所有组合
        // 0...0 - 0...0
        auto is_all_zero = [](string val) -> bool {
            for (int i=0; i<val.length(); ++i) 
                if (val[i]=='1') return false;
            return true;
        };
        if (is_all_zero(target) && is_all_zero(s)) return true;
        if (is_all_zero(target) || is_all_zero(s)) return false;
        return true;
    }

};