#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 构造题
class Solution {
public:
    vector<int> constructArray(int n, int k) {
        // 自行解答，
        // 思路  按顺序排序 1, 2, 3, ... , n
        //      构造 k，k-1,..., 1 的 |a_i+1 - a_i| 的值
        // k+1 - 1 = k 将 1 插入到 k 之后， k+1 - 1, k - 1, 有了 k,k-1 两个值
        //             将 2 插入到 k - 1 之后，有了 k - 2, k - 3 两个值
        // 发现规律后，找到1,...x 需要插入的值，根据奇偶性 计算出 x，
        // 然后 从 x + 1（或 x+2) 开始 插入 x, x-1, 直至 1

        vector<int> ans;
        int end = k + 1, begin = (end+1) / 2, x = begin - 1;

        ans.push_back(begin++);

        if (end % 2 == 0) ans.push_back(begin++); // end 为偶数时，从 x + 2开始插入
        while (x) ans.push_back(x--), ans.push_back(begin++);

        for (int i=end+1; i<=n; i++) ans.push_back(i); // 按顺序插入 end 后面的数字

        return ans;   
    }
};