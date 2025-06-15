#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 4.3 队列 - 双端队列
class Solution {
public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        int m = workers.size(), n = tasks.size();
        sort(tasks.begin(), tasks.end());
        sort(workers.begin(), workers.end());


        auto check = [&](int k) -> bool {
            int i = 0, p = pills;
            deque<int> valid_tasks;
            for (int j=m-k; j<m; ++j) {
                int w = workers[j];
                while (i < k && tasks[i] <= w+strength) {
                    valid_tasks.push_back(tasks[i]);
                    i++;
                }
                if (valid_tasks.empty()) return false;
                if (w >= valid_tasks.front()) {
                    valid_tasks.pop_front();
                    continue;
                }
                if (p == 0) return false;
                p--;
                valid_tasks.pop_back();
            }
            return true;
        };
        // 开区间写法
        int left=-1, right = min(m,n) + 1;
        while (left+1<right) {
            int mid = left + (right-left) / 2;
            (check(mid)?left:right) = mid;
        }
        return left;
    }
};