#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.7 摩尔投票法
class Solution {
public:
    int minimumIndex(vector<int>& nums) {
        // 自行解答 按题意模拟， 
        // nums的支配元素为 x ，则两个子数组的相同的支配元素也必定为 x
        int mx_cnt = 0, x = 0; unordered_map<int, int> cnt;
        for (auto & v:nums) {
            cnt[v] ++;
            if (cnt[v] > mx_cnt) {
                mx_cnt = cnt[v]; x = v;
            }
        }

        int n = nums.size(), x_cnt = 0;
        for (int i=0; i<n; ++i) {
            if (nums[i] == x) x_cnt ++;
            if (x_cnt > (i + 1)/2 && (mx_cnt - x_cnt)>(n-i-1)/2) return i;
        }
        return -1;        
    }
};