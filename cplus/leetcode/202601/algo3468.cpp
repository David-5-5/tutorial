#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.7 其他
class Solution {
public:
    int countArrays(vector<int>& original, vector<vector<int>>& bounds) {
        // 自行解答
        auto merge_interval = [] (vector<int> i1, vector<int> i2) -> vector<int> {
            if (i1[1] < i2[0] || i1[0] > i2[1]) return {};
            return {max(i1[0],i2[0]), min(i1[1], i2[1])};
        };

        vector<int> interval = bounds[0]; int n = original.size();
        for (int i = 1; i<n; ++i) {
            int diff = original[i] - original[i-1];
            interval[0] += diff, interval[1] += diff;
            interval = merge_interval(interval, bounds[i]);
            if (interval.size() == 0) return 0;
        }

        return interval[1] - interval[0] + 1;
    }


    int countArrays2(vector<int>& original, vector<vector<int>>& bounds) {
        // 参考题解 简化自行解答步骤，去掉函数调用

        int L = bounds[0][0], R = bounds[0][1]; int n = original.size();
        for (int i = 1; i<n; ++i) {
            int diff = original[i] - original[i-1];
            L = max(L+diff, bounds[i][0]);
            R = min(R+diff, bounds[i][1]);
            if (L > R) return 0;
        }

        return R - L + 1;
    }    
};