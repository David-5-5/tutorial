#include <iostream>
using namespace std;
const int maxn = 13010;
int n, W, w[maxn], v[maxn], f[maxn];

int main()
{
    // Input of console
    // n : count of goods
    // W : The weight of knapsack to hold goods
    cin >> n >> W;
    // loop line of n from console, each line is weight, value of goods
    for (int i = 1; i <= n; i++)
        cin >> w[i] >> v[i]; // 读入数据
    for (int i = 1; i <= n; i++)
        for (int l = W; l >= w[i]; l--)
            if (f[l - w[i]] + v[i] > f[l])
                f[l] = f[l - w[i]] + v[i]; // 状态方程
    cout << f[W];
    return 0;
}