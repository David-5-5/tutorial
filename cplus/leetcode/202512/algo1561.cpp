#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.1 从最小/最大开始贪心
class Solution {
public:
    int maxCoins(vector<int>& piles) {
        // 自行解答
        int i = 0, j = piles.size() - 1; long long ans = 0;
        sort(piles.begin(), piles.end());

        while (i < j) {
            ans += piles[j-1];
            i ++, j -= 2;
        }
        return ans;        
    }
};