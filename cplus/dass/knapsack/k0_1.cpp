#include <iostream>
using namespace std;
const int maxn = 13010;
int n, W, w[maxn], v[maxn], f[maxn];

/**
 * 由于每个物体只有两种可能的状态(取与不取), 对应二进制中的 0 和 1,
 * 这类问题便被称为 [0-1 背包问题]
 */
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

/**
 * ~~~~~~~~~~~~ THE TUTORIAL ~~~~~~~~~~~~
 * 1, 简化
 * 状态转移方程：f(i,w)=max(f(i-1,w),f(i-1,w-w[i])+v[i])
 * 选择到前i-1件物品，而不选择第i件物品，它能装的最大价值，也就是f(i-1,w)，以及我需要选择第i件物品，也就是f(i-1)，
 * 需要为这第i件物品，空出它耗费的空间w[i]，也就是小w-w[i]，当容量为w-w[i]时，装入一个w[i]体积的第i件物品后，
 * 她的当前容量就是w，那么f(i-1,w-w[i])就是没有装第i个物品时的背包总价值；放入第i件物品后的背包总价值就是
 * f(i-1,w-w[i])+v[i]，要和上一个状态(不放第i件产品的)比较价值大小
 * 
 * 由于对 f(i) 有影响的只有 f(i-1)，可以去掉第一维，直接用 f(w) 来表示处理到当前物品时背包容量为w的最大价值，得出以下方程：
 * f(w)=max(f(w),f(w-w[i])+v[i])
 * 
 * 2, 避免错误实现
 *  for (int i = 1; i <= n; i++)
 *      for (int l = 0; l <= W - w[i]; l++)
 *          f[l + w[i]] = max(f[l] + v[i], f[l + w[i]]);
 * 
 * 仔细观察代码可以发现：对于当前处理的物品 i 和当前状态 f_{i,j}，在 j >= w_{i} 时，f_{i,j} 是会被
 * f_{i,j-w_{i}} 所影响的。这就相当于物品 i 可以多次被放入背包，与题意不符。（事实上，这正是完全背包问题的解法）
 * 
 * 为了避免这种情况发生，我们可以改变枚举的顺序，从 W 枚举到 w_{i}，这样就不会出现上述的错误，
 * 因为 f_{i,j} 总是在 f_{i,j-w_{i}} 前被更新。
*/