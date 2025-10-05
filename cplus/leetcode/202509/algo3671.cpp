#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.8 互质
// 树状数组模板 
template<typename T>
class FenwickTree {
    vector<T> tree;

public:
    // 使用下标 1 到 n
    FenwickTree(int n) : tree(n + 1) {}

    // a[i] 增加 val, 1 <= i <= n
    void update(int i, T val) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }

    // 求前缀和 a[1] + ... + a[i] 1 <= i <= n
    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) { // i-= i&-i
            res += tree[i];
        }
        return res;
    }

};

// 模板一预处理每个数的所有不同质因子
const int N = 7 * 1e4 + 1;
vector<int> factors[N]; // 包括所有的因子，不仅是质因子

int init = [] {
    for (int i = 1; i < N; ++i) 
        for (int j = i; j < N; j += i) 
            factors[j].push_back(i);            

    return 0;
}();

class Solution {
public:
    int totalBeauty(vector<int>& nums) {
        // 参考题解 倍数容斥(3312) + 树状数组(值域)
        const int mod = 1e9 + 7;
        int mx = ranges::max(nums);
        
        auto cnt_subseq = [&] (vector<int>& b, int g) -> long long {
            FenwickTree<long long> ft(mx / g);
            long long res = 0;
            for (int x: b) {
                x /= g;
                long long cnt = ft.pre(x-1) + 1;
                cnt %= mod; res += cnt;
                ft.update(x, cnt);
            }
            return res;
        };
        vector<vector<int>> grp(mx+1);
        for (auto x: nums) for (auto f:factors[x]) grp[f].push_back(x);

        long long ans = 0; vector<int> gcd_cnt(mx+1);

        for (int i = mx; i>0; --i) {
            long long res = cnt_subseq(grp[i], i);
            for (int j=i*2; j<=mx; j+=i) {
                res -= gcd_cnt[j];
            }
            gcd_cnt[i] = res % mod;
            ans += 1LL * gcd_cnt[i] * i;
        }
        return (ans % mod + mod) % mod;
    }
};