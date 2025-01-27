#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
int s[1001][1001];

// 第二类斯特林数 预处理 模板 不同的元素分到互不区分的集合中
auto init = [] {
    s[0][0] = 1;
    for (int i=1; i<1001; i++) {
        for (int j=1; j<1001; j++) {
            s[i][j] = (s[i-1][j-1] + (long long)j * s[i-1][j]) % MOD;
        }
    }
    return 0;
}();


// 双周赛 141
class Solution {
public:
    int numberOfWays(int n, int x, int y) {
        long long ans = 0, perm = 1, pow_y = 1;
        for (int i=1; i<=min(n,x); i++) {
            perm = perm * (x-i+1) % MOD; // 节目就是集合，不同节目需要区分
            pow_y = pow_y * y % MOD;    // 乘以 1 个 y，表示增加一个节目的分数为[1..y]种情况
            // 两数相乘后紧跟 %MOD，超出 long long
            ans = (ans + perm * s[n][i] % MOD * pow_y) % MOD;
        }
        return ans;  
    }
};