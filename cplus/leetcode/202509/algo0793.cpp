#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.4 阶乘分解
class Solution {
public:
    int preimageSizeFZF(int k) {
        // 暴力 - O(N)
        int tot = 0;
        long long i = 5;
        while(true) {  
            if (tot == k) return 5;
            if (tot > k) return 0;            
            auto comp = i;
            while (comp % 5 == 0) {
                comp /= 5;
                tot ++;
            }
            i += 5;
        }
    }

    int preimageSizeFZF2(int k) {
        auto right = 5L * k, left = 4L * k;
        // 二分查找 开区间
        while (left+1 < right) {
            auto mid = (left + right) / 2;
            int tot = 0;
            while (mid) {
                mid /= 5;
                tot += mid;
            }
            if (tot < k) left = (left + right) / 2;
            else right = (left + right) / 2;    // 二分结果为 right
        }
        
        // 查找确定数的阶乘末尾 0 的数量 leetcode 172  log N的算法
        int tot = 0;            // 检查 right 包含的 0 是否等于 k
        while (right) {
            right /= 5; tot += right;
        }
        return tot == k?5:0;
    }
};