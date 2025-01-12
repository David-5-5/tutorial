#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 思维题 - 从特殊到一般
class Solution {
public:
    int shortestSequence(vector<int>& rolls, int k) {
        // 参考题解，实质上将 rolls 分组，每组个子数组包含都 1-k 这 k 个数
        // 分组 + 1 即是无法从子序列中的得到的最短子序列

        int ans = 1;
        unordered_set<int> mask;
        
        for (auto x : rolls) {
            mask.emplace(x);
            if (mask.size() == k) 
                ans += 1, mask.clear();
        }

        return ans;
    }

    int shortestSequence(vector<int>& rolls, int k) {
        // C++ 不同写法，参考题解
        int ans = 1, left = k, mask[k+1];
        memset(mask, 0, sizeof(mask));

        for (auto x : rolls) {
            
            if (mask[x] < ans) {
                mask[x] = ans;
                if (--left == 0) 
                    ans += 1, left = k;
            }
        }

        return ans;
    }    
};