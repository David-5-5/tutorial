#include <bits/stdc++.h>
using namespace std;


// comb 模板
/**
 * According to Fermat's theorem, if m is a prime number, 
 * we can compute x^{n mod (m-1)} to speed up the algorithm
 * 带模算的快速幂
 */
long long pow(long long base, int exp, int modulo)
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
    return res;
}

const int MOD = 1e9 + 7;
const int MX = 1e5;   // 根据取值范围进行变更

long long fact[MX+1];
long long i_fact[MX+1];
auto init = [] {
    fact[0] = 1;
    for (int i=1; i<MX+1; i++) {
        fact[i] = fact[i-1] * i % MOD;
    }
    i_fact[MX] = pow(fact[MX], MOD-2, MOD);
    for (int i=MX; i; i--) {
        i_fact[i-1] = i_fact[i] * i % MOD;
    }
    return 0;
}();

long long comb(int n, int m) {
    if (m > n) return 0;
    return (fact[n] * i_fact[m] % MOD) * i_fact[n-m] % MOD;
}
// comb 模板

// 一般树 - 3.2 自顶向下 DFS
class Solution {
public:
    int assignEdgeWeights(vector<vector<int>>& edges) {
        // 自行解答
        // 排列组合， x 个 1 和 y 个 2 的排列，x 必须为 奇数 x + y = d
        // 数量比较大 d!/x!*y! % m = d!%m * inv(x!*y!%m)
        int n = edges.size() + 1; vector<vector<int>> g(n, vector<int>());
        for (const auto& edge : edges) {
            int u = edge[0]-1, v = edge[1]-1;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }

        auto dfs = [&] (this auto&& dfs, int u, int fa) -> int {
            int dep = 0;
            for (auto & v: g[u]) {
                if (v == fa) continue;
                dep = max(dep, dfs(v, u));
            }
            return dep + 1;
        };

        int depth = dfs(0, -1) - 1, ans = 0;

        for (int i=1; i<=depth; i+=2) {
            ans = (comb(depth, i) + ans) % MOD;
        }
        return ans;
    }

    int assignEdgeWeights2(vector<vector<int>>& edges) {
        // 参考题解
        // 排列组合， x 个 1 和 y 个 2 的排列，x 必须为 奇数 x + y = d
        // 数量比较大 d!/x!*y! % m = d!%m * inv(x!*y!%m)
        // 数学不会了，上面的排列加起来其实就是 2 ^ (d-1) 不需要comb，直接用pow 就可以了
        int n = edges.size() + 1; vector<vector<int>> g(n, vector<int>());
        for (const auto& edge : edges) {
            int u = edge[0]-1, v = edge[1]-1;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }

        auto dfs = [&] (this auto&& dfs, int u, int fa) -> int {
            int dep = 0;
            for (auto & v: g[u]) {
                if (v == fa) continue;
                dep = max(dep, dfs(v, u));
            }
            return dep + 1;
        };

        int depth = dfs(0, -1) - 1;
        return pow(2, depth-1, MOD);
    }    
};