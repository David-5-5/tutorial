#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.5 因子
class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        // 自行解答
        int ans = 0;
        for (const auto& v: nums) {
            int cnt = 0, val = 0;
            for (int i=2; i*i<v; ++i) if (v%i == 0){
                cnt++; if (cnt>1) break;
                // 一定要判断 i * i == v 的情况
                if (i * i == v) {cnt = 0; break;}
                val += i + v / i;
            }

            if (cnt == 1)  {
                // cout << v << ", " << val + v + 1 << endl;
                ans += val + v + 1;
            }
        }
        return ans;      
    }

    int sumFourDivisors(vector<int>& nums) {
        // 暴力，为了排除上面代码的 bug
        int ans = 0;
        for (const auto& v: nums) {
            set<int> primes;
            for (int i=1; i*i<=v; ++i) {
                if (v%i == 0) {
                    primes.insert(i); primes.insert(v/i);
                }
            }

            if (primes.size() == 4) {
                // cout << v << ", " << accumulate(primes.begin(), primes.end(), 0) << endl;
                ans += accumulate(primes.begin(), primes.end(), 0);
            }
        }
        return ans;  
    }    
};