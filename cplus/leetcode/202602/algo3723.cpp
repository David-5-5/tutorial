#include <bits/stdc++.h>
using namespace std;

// 三、字符串贪心 - 3.1 字典序最小/最大
class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        // 自行解答 1094 ms
        string ans = ""; int left = sum;

        for (int _=0; _<num; ++_) {
            ans += to_string(min(left, 9));
            left -= min(left, 9);
        }
        
        return left?"":ans;
    }

    string maxSumOfSquares(int num, int sum) {
        // 性能优化 19 ms
        string ans(num, '0'); int left = sum;

        for (int i=0; i<num && left; ++i) {
            ans[i] = min(left, 9) + '0';
            left -= min(left, 9);
        }
        
        return left?"":ans;
    }
    
};