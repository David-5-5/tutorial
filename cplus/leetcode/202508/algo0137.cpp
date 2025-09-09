#include <bits/stdc++.h>
using namespace std;

// 位运算 - 其他
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        // 参考题解 位运算 二进制按位计算出现 1 出现的个数，然后 %3，为 1 就是出现一次的元素改位为 1
        // 时间复杂度 O(nlogn) 空间复杂度 O(1)
        int ans = 0;
        for (int i=0; i<32; i++) {
            int cnt = 0;
            for (auto val: nums) {
                if ((val >> i) & 1) cnt ++;
            }
            if (cnt % 3) ans |= 1 << i;
        }
        return ans;

    }

    int singleNumber2(vector<int>& nums) {
        // 参考题解 数字电路设计
        // 时间复杂度 O(n) 空间复杂度 O(1)
        int a = 0, b = 0;
        for (auto val: nums) {
            b = ~a & (b ^ val);
            a = ~b & (a ^ val);
        }
        return b;
    }

};