#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.1 从最小/最大开始贪心
class Solution {
public:
    long long maxWeight(vector<int>& pizzas) {
        // 自行解答，数组排序，在数组中取奇数天个最大值，
        // 然后从最大的值开始取最大值的次大值，取偶数天的次数
        int n = pizzas.size(), odd = (n/4 + 1) / 2;
        sort(pizzas.begin(), pizzas.end());
        
        long long ans = accumulate(pizzas.begin()+(n-odd), pizzas.end(), 0LL); // 奇数的和
        for (int _=0, inx=n-odd-1; _<n/4-odd; _++, inx -=2 ) {
            ans += pizzas[inx-1];  // 逐一加上偶数天的pizza
        }

        return ans;
    }
};