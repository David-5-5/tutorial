#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.2 脑筋急转弯
class Solution {
public:
    int countPermutations(vector<int>& complexity) {
        // 阅读理解，所有元素的complexity都需要大于 complexity[0]
        // 即要么结果为 0，要么为 n-1 的全排列
        const int mod = 1e9 + 7;
        int n = complexity.size();
        int ans = 1;
        for (int i=1; i<n; i++) {
            if (complexity[i]>complexity[0]) {
                ans = 1LL * ans * i % mod;
            } else return 0;
        }
        return ans;
    }
    
};