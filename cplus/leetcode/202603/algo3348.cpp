#include <bits/stdc++.h>
using namespace std;

// 三、字符串贪心 - 3.1 字典序最小/最大 倒序贪心
class Solution {
public:
    string smallestNumber(string num, long long t) {
        // prime 2, 3, 5, 7,
        // 初始 pre num中第一个零之前的数包含的质数数量
        //     suf 是 t 包含的质数数量减去 pre 的质数数量
        vector<vector<int>> pre;    // 记录前缀贡献给 t 的质数
        vector<int> suf(4);
        vector<int> primes = {2, 3, 5, 7};
        
        for (int p=0; p<4; ++p) {
            while (t % primes[p] == 0) {
                suf[p] ++; t /= primes[p];
            }
        }
        if (t>1) return "-1";

        // prime factors 1 <= val <= 9
        auto pf = [&](int val) -> vector<int> {
            vector<int> res(4);
            for (int p=0; p<4; ++p) {
                while (val % primes[p] == 0) {
                    res[p] ++; val /= primes[p];
                }
            }
            return res;
        };

        auto sub_inx = [&](int i) -> void {
            auto val = num[i] - '0';
            vector<int> factors = pf(val);
            for (int p=0; p<4; ++p) {
                factors[p] = min(factors[p], suf[p]);
                suf[p] -= factors[p];
            }
            pre.push_back(factors);
        };

        auto add_inx = [&](int i) -> void {
            for (int p=0; p<4; ++p) suf[p] += pre[i][p];
        };

        auto sub_val = [&](int val) -> void {
            vector<int> factors = pf(val);
            for (int p=0; p<4; ++p) {
                suf[p] -= factors[p];
            }            
        };

        auto count = [&](vector<int>& arr) -> int {
            return arr[0] + arr[1] + arr[2] + arr[3];
        };

        auto get_max = [&](int limit) -> int {
            if (count(suf) == 0) return limit;

            for (int v=limit-1; v>=2; v--) {
                vector<int> factors = pf(v);
                if (suf[0]>=factors[0] && suf[1]>=factors[1] &&
                    suf[2]>=factors[2] && suf[3]>=factors[3])
                    return v;
            }
            return 1;
        };

        auto equal = [&](int val) -> int {
            vector<int> factors = pf(val);
            return suf[0]==factors[0] && suf[1]==factors[1] && 
                suf[2]==factors[2] && suf[3]==factors[3];
        };

        int n = num.length(), pos0 = n;
        for (int i=0; i<n; i++) {
            if (num[i] == '0') {
                pos0 = i; break;
            }
            sub_inx(i);
        }

        string ans = "";
        
        for (int i=n-1; i>=0; --i) {
            if (count(suf) == 0) {ans.push_back(max(num[i], '1')); continue;}
            
            if (i<pos0) {
                add_inx(i);
                if (i) {
                    
                }
            }
            int val = get_max(i<pos0?num[i]-'0':2);

            if (val < (num[i]-'0') && equal(val)) {
                for (int p=0; p<4; ++p) if (suf[p]) {
                    val /= primes[p];
                }
            }
            sub_val(val); ans.push_back(val + '0');
        }

        while (count(suf)) {
            auto val = get_max(2); sub_val(val);
            ans.push_back(val + '0');
        }

        reverse(ans.begin(), ans.end()); return ans;   
    }    
};
