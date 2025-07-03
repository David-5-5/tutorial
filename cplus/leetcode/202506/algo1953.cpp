#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.3 堆 - 重排元素
class Solution {
public:
    long long numberOfWeeks(vector<int>& milestones) {
        // 自行解答，不需要堆，脑筋急转弯
        long long sum = 0;
        int mx = 0;
        for (auto v:milestones) {
            sum += v;
            mx = max(mx, v);
        }
        if (mx < sum/2 + 1) return sum; // 最大值小于总和的一半
        else return (sum-mx)*2 + 1;     
    }
};