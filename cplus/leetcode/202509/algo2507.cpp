#include <bits/stdc++.h>
using namespace std;

// 模板一预处理每个数的所有不同质因子
// const int N = 1e5 + 1;
// vector<int> prime_factors[N];

// int init = [] {
//     for (int i = 2; i < N; ++i) {
//         if (prime_factors[i].empty()) { // 质数
//             for (int j = i; j < N; j += i) {
//                 prime_factors[j].push_back(i);
//             }
//         }
//     }
//     return 0;
// }();

// 模板二 预处理 x 的 最小质因子 LPF(lower prime factor) lpf(x)
const int N = 1e5 + 1;
int lpf[N];

int init = [] {
    memset(lpf, 0, sizeof(lpf));

    for (int i = 2; i < N; ++i) {      
        if (lpf[i] == 0) { // 质数
            for (int j = i; j < N; j += i) {
                if (lpf[j] == 0) lpf[j] = i;   // 质数 x 的 lpf(x) == x
            }
        }
    }
    return 0;
}();

// prime_factor(45) = {{3,2}, {5,1}} 45 = 3^2 * 5^1
// prime_factor(16) = {{2,4}} = 2^4
vector<pair<int, int>> prime_factors(int x) {
    vector<pair<int, int>> res;
    while (x > 1) {
        int p = lpf[x], e = 1;
        for (x/=p; x % p == 0; x /= p) e ++;
        res.emplace_back(p, e);
    }
    return res;
}

// 数学算法 - 数论 - 1.3 质因数分解
class Solution {
public:
    int smallestValue(int n) {
        vector<pair<int, int>> res = prime_factors(n);
        int tot = 0; for (auto& [a, e]:res) tot += a * e;
        if (tot == n) return n;
        else return smallestValue(tot);
    }
};