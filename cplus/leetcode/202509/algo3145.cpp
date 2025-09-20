#include <bits/stdc++.h>
using namespace std;

const int mx = 50;
vector<long long> pres(mx); 
int init = [] {
    pres[0] = 1L;                // 2^0 = 1
    for (int i=1; i<mx; ++i) {  // i is exponent
        pres[i] = pres[i-1] * 2 + (1L << i);
    }
    return 0;
}();

long long qpow(long long base, long long exp, long long modulo)
{
    base %= modulo;
    long long res = 1;
    while (exp > 0)
    {
        if (exp & 1)
            res = res * base % modulo;
        base = base * base % modulo;
        exp >>= 1;
    }
    return res % modulo;
}

// 位运算 - 试填法
class Solution {
public:
    vector<int> findProductsOfElements(vector<vector<long long>>& queries) {
        // 自行解答
        auto count = [] (this auto&& count, long long val) -> long long {
            // 1 到 val 包含的每个数字包含的二进制 1 的数量之和
            if (val == 0) return 0;
            if (val == 1) return pres[0];

            int e = bit_width((unsigned long long) val) - 1;
            return val - (1L << e) + 1 + count(val - (1L<<e)) + pres[e-1];
        };

        unordered_map<long long, long long> memo;
        auto inner = [&](this auto&& inner, long long val) -> long long {
            if (val == 0 || val == 1) return 0;
            if (val == 2) return 1;
            if (memo.count(val)) return memo[val];
            long long e = bit_width((unsigned long long) val) - 1;
            return memo[val] = e * (val-(1L<<e)+1) + inner(val-(1L<<e)) + inner((1L<<e)-1);
        };

        auto mul = [&] (long long val, long long cnt) -> long long{
            long long  n_val = val, f_cnt = count(val);
            if (cnt < f_cnt) n_val --;
            
            long long res = inner(n_val), diff = cnt - count(n_val); 

            for (int _=0; _<(diff); ++_) {
                long long lb = val & -val;
                res += bit_width((unsigned long long) lb) - 1;
                val -= lb;
            }
            return res;
        };
        
        // cout << mul(9, 15) << endl;

        vector<int> ans;
        for (auto q: queries) {
            long long start = q[0] + 1, end = q[1] + 1; int mod = q[2];
            if (mod == 1) {
                ans.push_back(0); continue;
            }
            auto find_val = [&] (long long cnt) -> long long {
                auto it = ranges::upper_bound(pres, cnt);
                if (it == pres.begin() || *prev(it) == cnt) return (1 << it-pres.begin())-1;
                long long left = (1L << it-pres.begin())-1, right = (1L << it-pres.begin()+1);
                while (left + 1 < right) {
                    auto mid = (left + right) / 2;
                    if (count(mid) < cnt) left = mid;
                    else right = mid;
                }
                return right;
            };
            auto start_val = find_val(start-1), end_val = find_val(end);
            auto exponent = mul(end_val, end) - mul(start_val, start-1);
            ans.push_back(qpow(2, exponent, mod));
        }

        return ans;
    }
};

int main() {
    // 显式声明内层vector<long long>，强化类型信息
    vector<vector<long long>> queries = {vector<long long>{169879810433127,550761388797555,99654}};
    cout << Solution().findProductsOfElements(queries)[0] <<endl;
    return 0;
}