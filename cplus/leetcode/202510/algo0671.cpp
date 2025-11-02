#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.1 相向双指针
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        // 自行解答
        int n = numbers.size(); vector<int> ans = {1, n};
        while (true) {
            int & l = ans[0], & r = ans[1]; // int& 不是类型，& 需要加在取地址的每个变量前
            if (numbers[l-1] + numbers[r-1] == target) return ans;
            else if ((numbers[l-1] + numbers[r-1] > target)) r--;
            else l ++;
        }  
    }
};