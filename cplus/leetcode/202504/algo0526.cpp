#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.1 排列型 - 相邻无关
class Solution {
public:
    int countArrangement(int n) {
        // 自行解答
        vector<int> memo(1<<n, -1);
        auto dfs = [&] (this auto&& dfs, int state) -> int {
            if (state == 0) return 1;
            
            auto& res = memo[state];
            if (res != -1) return res;

            int i = n - __builtin_popcount(state); // 计算包含一个个数，减少一个递归参数
            res = 0;
            for (int j=0; j<n; j++) {
                // 位运算 和 比较符 !!! 多加括号
                if (((state >> j) & 1) && ((i+1) % (j+1)==0 || (j+1) % (i+1)==0)) {
                    res += dfs(state - (1 << j)) ;
                }
            }

            return res;
        };

        return dfs((1<<n)-1);
    }
};

int main() {
    cout << Solution().countArrangement(2);
}