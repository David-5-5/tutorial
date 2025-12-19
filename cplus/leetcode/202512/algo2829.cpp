#include <bits/stdc++.h>
using namespace std;

// 数学算法 7.7 其他
class Solution {
public:
    int minimumSum(int n, int k) {
        // 自行解答 hash表
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
};