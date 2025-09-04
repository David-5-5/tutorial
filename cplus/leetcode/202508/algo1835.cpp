#include <bits/stdc++.h>
using namespace std;

// 位运算 - 拆位 / 贡献法
class Solution {
public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        // 计算arr2的异或和，初始值为0
        int xor_arr2 = accumulate(arr2.begin(), arr2.end(), 0, 
            [](int acc, int val) { return acc ^ val; });
        
        // 对arr1中的每个元素执行 x & xor_arr2，再计算异或和
        int result = accumulate(arr1.begin(), arr1.end(), 0,
            [&](int acc, int val) { return acc ^ (val & xor_arr2); });
        
        return result;
    }
};
