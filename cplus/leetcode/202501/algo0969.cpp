#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 构造题
class Solution {
public:
    vector<int> pancakeSort(vector<int>& arr) {
        // 参考题解，学习 c++ 语法，其实也特别方便
        vector<int> ans;

        for (int i=arr.size(); i; i--) {
            int inx = max_element(arr.begin(), arr.begin()+i) - arr.begin();
            if (inx + 1 == i) continue;

            reverse(arr.begin(), arr.begin() + inx + 1);
            reverse(arr.begin(), arr.begin() + i);
            ans.push_back(inx+1);
            ans.push_back(i);
        }

        return ans;
    }
};