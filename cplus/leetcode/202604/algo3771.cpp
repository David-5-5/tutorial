#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.5 贡献法
class Solution {
public:
    long long totalScore(int hp, vector<int>& damage, vector<int>& requirement) {
        // 自行解答 逆序前缀和，展开解题思路：
        // score[1]         ...                          score[j]         ...       score[n]
        // hp-d[1]>=r[1]                
        // hp-(d[1]..d[j])>=r[j]  hp-(d[i]..d[j])>=r[j]  hp-(d[j])>=r[j]
        // hp-(d[1]..d[n])>=r[n]  hp-(d[i]..d[n])>=r[j]  hp-(d[j]..d[n])>=r[n]      hp-d[n]>=r[n]
        // 计算不是单独计算每列 score[j],而应以 行 进行
        // 核心就是 O(1) 时间找出最小的 i 且 hp-(d[i]..d[j])>=r[j]，这样对于 r[j]，贡献的得分为 j - i + 1
        int n = damage.size(); vector<int> rev_pres(n+1);
        // Reverse prefix sum
        for (int i=1; i<=n; i++) {
            rev_pres[i]= rev_pres[i-1] + damage[n-i];
        }

        long long ans = 0;
        for (int i=1; i<=n; i++) {
            auto val = hp + rev_pres[i-1] - requirement[n-i];   // 点睛之笔
            auto cnt = ranges::upper_bound(rev_pres, val) - rev_pres.begin() - i;
            if (cnt > 0) ans += cnt;
        }

        return ans;  
    }
};