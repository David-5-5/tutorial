#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 四、双序列双指针 - 4.1 双指针
class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        // 自行解答
        int n = firstList.size(), m = secondList.size();
        int f = 0, s = 0;

        vector<vector<int>> ans;
        while (f < n && s < m) {
            int a0 = firstList[f][0], a1 = firstList[f][1];
            int b0 = secondList[s][0], b1 = secondList[s][1];
            if (!(a0 > b1 || b0 > a1))  { // 有交集
                ans.push_back({max(a0, b0), min(a1, b1)});
            }

            if (a1 > b1) s++;
            else f++;
        }

        return ans;        
    }
};