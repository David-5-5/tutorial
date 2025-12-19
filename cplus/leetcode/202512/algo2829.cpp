#include <bits/stdc++.h>
using namespace std;

// 数学算法 7.7 其他
class Solution {
public:
    int minimumSum(int n, int k) {
        // 自行解答 hash表 O(NlogN)
        unordered_set<int> val; int start = 1, ans = 0;
        while (val.size() < n) {
            if (!val.count(k - start)) {
                ans += start;
                val.insert(start);
            }
            start ++;
        }

        return ans;
    }

    int minimumSum2(int n, int k) {
        // 参考题解 等差数列 O(1)
        int h = min(n,k/2);
        int ans = (1 + h) * h/ 2;
        if (n > h) ans += (k + k+n-h-1) * (n-h) /2 ;

        return ans;
    }    
};