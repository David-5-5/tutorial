#include <bits/stdc++.h>
using namespace std;


// 数学算法 - 数论 - 1.6 最大公约数（GCD）
class Solution {
public:
    int countDifferentSubsequenceGCDs(vector<int>& nums) {
        // 参考题解 - 反向思考，对于每个值 1～mx 查找其倍数是否都存在
        // 总体是 调和级数的时间复杂度 ~ O(N logN)
        int mx = ranges::max(nums);
        vector<bool> exist(mx+1), gcds(mx+1);
        for (auto x: nums) exist[x] = true;
        
        for (int i=1; i<=mx; ++i) {
            int g = 0;
            for (int j=i; j<=mx; j+=i) {
                if (exist[j]) g = gcd(g, j);
                if (g == i) break; // 剪枝，优化
            }
            if (g == i) gcds[i] = true;
        }
        int ans = 0; for (int i=1; i<=mx; ++i) if (gcds[i]) ans ++;
        return ans;
    }
};