#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.7 分类讨论
class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        
        long long ans = min(1LL * cost1 * need1 + 1LL * cost2 * need2, 1LL * costBoth * (max(need1, need2)));

        if (need1 > need2) ans = min(ans, 1LL * need2 * costBoth + 1LL* cost1 * (need1-need2));
        else ans = min(ans, 1LL * need1 * costBoth + 1LL* cost2 * (need2-need1));
        return  ans;   
    }
};