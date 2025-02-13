#include <bits/stdc++.h>
using namespace std;

// 与 2035 类似
class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        // 折半搜索 + 两数之和
        int n = nums.size() / 2;
        int ans = INT_MAX;
        vector<int> v1, v2;

        /**
         * 把 nums 的前 n 个数分成两个数组，数组中元素数量可以不同。记 s1 为第一个数组的和，
         * s2 为第二个数组的和，请算出一个列表 v1[i] 表示 nums 中前 n 个数有 i 个被划分到
         * 第一个数组的情况下，(s1−s2) 有哪些可能的值
         */
        auto f = [&](int begin, vector<int>& v) {
            // (1<<n) i 中二进制第 j 位为 1 的数表示 nums[j] 属于第一组
            int len = begin == 0 ? n : nums.size() - n;
            for (int i=0; i<(1<<len); i++) {
                int sm = 0;
                for (int j=0; j<len; j++) {
                    if (i>>j & 1) sm += nums[begin+j];
                }
                v.push_back(sm);
            }

            sort(v.begin(), v.end());
        };

        f(0, v1); f(n, v2);

        // for (int i=0; i<v1.size(); i++) {
        //     // 二分查找 ranges::lower_bound 
        //     int k = ranges::lower_bound(v2, goal-v1[i]) - v2.begin();
        //     if (k<v2.size()) ans = min(ans, abs(goal- v1[i] - v2[k]));
        //     if (k>0) ans = min(ans, abs(goal-v1[i]-v2[k-1]));
        // }
        for (int i=0, k=v2.size()-1; i<v1.size(); i++) {
            // 双指针
            while (k>=0 && v2[k]+v1[i] > goal) k--;
            if (k+1<v2.size()) ans = min(ans, abs(goal- v1[i] - v2[k+1]));
            if (k>=0)ans = min(ans, abs(goal-v1[i]-v2[k]));
        }

        return ans;

    }
};