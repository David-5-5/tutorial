#include <bits/stdc++.h>
using namespace std;

/**
 * 解题思路:
 * 对输入的 t,p 按 t = 1,2 在两个队列中进行排序
 * 选择规则
 * 1, 当 t = 1 or t = 2 的数量为 0 时, 从大到小(升序排列，从队列尾取数) 取存在数的队列，并不断将剩余空间减少至 0
 * 2, 当 t = 1 和 t = 2 都存在时，比较 t = 2 队列尾的 p 值与 t = 1 队列尾部的两最大的 p 值之和的大小(占用空间一致)
 *    2.1, p[t==2] > p[t==1], 取 t == 2 队列的尾部值
 *    2.2, p[t==2] <= p[t==1], 取 t == 1 队列的尾部值
 * 注意：
 *    a. 由于需要输出构成最佳集的车辆编号，因此vector中使用pair<p,i>, p为输入的p值, i 为输入的编号，从1开始计数
 *    b. p[t==2] <= p[t==1], 仅取 t == 1 队列的尾部值的最大一个值，而不是两个值.
 *       避免出现 t1[n-1] + t1[n-2] > t2[n-1], t1[n-1] + t2[n-1] 是最优的情况
 *
 */
int n, v;
vector<pair<int, int>> kayaks;
vector<pair<int, int>> catamarans;

void solution()
{
    sort(kayaks.begin(), kayaks.end());
    sort(catamarans.begin(), catamarans.end());

    int left = v;
    int sumv = 0;
    vector<int> result;
    while (left > 0 && (kayaks.size() > 0 || catamarans.size() > 0))
    {
        if (left == 1 and kayaks.size() == 0)
            break;
        if (kayaks.size() == 0)
        {
            while (left > 1 && catamarans.size() > 0)
            {
                sumv += catamarans.back().first;
                result.emplace_back(catamarans.back().second);
                left -= 2;
                catamarans.pop_back();
            }
            break;
        }
        if (catamarans.size() == 0)
        {
            while (left > 0 && kayaks.size() > 0)
            {
                sumv += kayaks.back().first;
                result.emplace_back(kayaks.back().second);
                left -= 1;
                kayaks.pop_back();
            }
            break;
        }
        if (left == 1)
        {
            sumv += kayaks.back().first;
            result.emplace_back(kayaks.back().second);
            left -= 1;
            kayaks.pop_back();
        }
        else
        {
            int kv = kayaks.back().first;
            if (kayaks.size() > 1)
            {
                kv += kayaks[kayaks.size() - 2].first;
            }
            if (catamarans.back().first > kv)
            {
                sumv += catamarans.back().first;
                result.emplace_back(catamarans.back().second);
                left -= 2;
                catamarans.pop_back();
            }
            else
            {
                sumv += kayaks.back().first;
                result.emplace_back(kayaks.back().second);
                left -= 1;
                kayaks.pop_back();
            }
        }
    }

    cout << sumv << endl;
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
}

int main()
{

    cin >> n >> v;
    for (int i = 0; i < n; i++)
    {
        int t, p;
        cin >> t >> p;
        if (t == 1)
        {
            kayaks.emplace_back(make_pair(p, i + 1));
        }
        else
        {
            catamarans.emplace_back(make_pair(p, i + 1));
        }
    }
    solution();
}