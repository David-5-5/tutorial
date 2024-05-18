#include <bits/stdc++.h>
using namespace std;

/**
 * n 辆同样车辆的 left/right 的组合数
*/
long long combi(int cnt) {
    // 数量为 0, 返回 1
    if (cnt == 0) return 1;
    // 初始为 3，与 n 辆相同品牌的车不同，否则 n + 1相同的车
    long long res = 3;
    // 多于一辆车，与 n 辆相同品牌的车不紧邻的车有 4 种品牌
    for (int i=1; i<cnt; i++){
        res *= 4;
    }
    return res;
}

int main()
{
    int n;
    cin >> n;
    
    long long ans = 0;
    // n 辆同样车辆的两边的数量为 i, n-2-i
    for (int i=0; i<=n-2; i++) {
        // 两边数量的组合数量
        ans += combi(i) * combi(n-2-i);
    }
    // 有 4 种品牌的 n 辆车，因此乘以 4
    cout << ans * 4 << endl;
}