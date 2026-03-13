#include <bits/stdc++.h>
using namespace std;

// 四、数学贪心 - 4.3 排序不等式
class Solution {
public:
    long long maxScore(int n, vector<vector<int>>& edges) {
        // 脑筋急转弯 不需遍历 edges
        long long ans = 1LL * n * (n - 1); int cur = n - 2;
        deque<int>  q; q.emplace_back(n); q.emplace_back(n-1);

        while (cur) {
            int x = q.front(); q.pop_front();
            ans += 1LL * x * cur; q.push_back(cur); cur --;
        }

        return (edges.size() == n)?ans + 2: ans;   

    }

};