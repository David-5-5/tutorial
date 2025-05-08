#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 数位 DP
class Solution {
public:
    int countNumbers(string l, string r, int b) {
        // 参考题解 转 b 进制 没有思路，其实很简单，要是用 python 就更简单
        const int mod = 1e9 + 7;
        
        // BEGIN -- 转 b 进制 模板 template
        auto trans = [&](string s) -> vector<int> {
            vector<int> digits;
            for (auto& c:s) c -= '0';   // 变为不可见字符
            while (!s.empty()) {
                string nxt_s;
                int rem = 0;
                for (auto& c:s) {
                    rem = rem * 10 + c;
                    int q = rem / b;   //商
                    if (q || !nxt_s.empty()) {
                        nxt_s.push_back(q);
                    }
                    rem = rem % b;
                }
                digits.push_back(rem);
                s = move(nxt_s);
            }

            ranges::reverse(digits);
            return digits;
        };
        // END -- 转 b 进制 模板 template

        vector<int> low = trans(l);
        vector<int> high = trans(r);
        int n = high.size(), diff = n - low.size();

        unordered_map<int, int> memo;
        // q 是 quotient 前一个数的商，r 是上一个数的余数
        auto f = [&] (this auto&& f,int i, int pre,  bool is_low, bool is_upper) -> int {
            if (i == n) return 1;

            int mask = i << 6 | pre << 2 | is_low << 1 | is_upper;
            if (memo.count(mask)) return memo[mask];

            int lo = is_low && i >= diff?int(low[i-diff]) : 0;
            int hi = is_upper ? high[i]: b-1;
            
            int res = 0;
            for (int d=max(pre,lo); d<=hi; ++d) {
                res = (res + f(i+1, d, is_low && d == lo, is_upper && d == hi))%mod;
            }
            return memo[mask] = res;
        };

        return f(0, 0, true, true);  
    }
};