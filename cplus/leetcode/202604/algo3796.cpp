#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.6 两次扫描
class Solution {
public:
    int findMaxVal(int n, vector<vector<int>>& restrictions, vector<int>& diff) {
        // 参考题解的写法，很巧妙!!
        vector<int> max_val(n, INT_MAX), arr(n);

        for (auto v:restrictions) {
            max_val[v[0]] = v[1];
        }

        for (int i=0; i<n-1; i++) {
            arr[i+1] = min(arr[i] + diff[i], max_val[i+1]);
        }
        for (int i=n-2; i; i--) {
            arr[i] = min(arr[i], arr[i+1]+diff[i]);
        }

        return ranges::max(arr);
    }
};