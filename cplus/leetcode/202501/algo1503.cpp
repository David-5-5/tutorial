#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 脑筋急转弯
class Solution {
public:
    int getLastMoment(int n, vector<int>& left, vector<int>& right) {
        // 自行解答，两只蚂蚁相遇同时换方向，实质上同两只蚂蚁继续前进
        return max(left.size()?ranges::max(left):0, right.size()?n - ranges::min(right):0);
    }
};