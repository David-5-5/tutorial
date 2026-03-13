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

    long long maxScore2(int n, vector<vector<int>>& edges) {
        // 数学
        long long ans = 1LL * n * (n - 1) + 1LL * n * (n-2); 

        for (int i = n-1; i>=3; i--) {
            ans += 1LL * i * (i-2);
        }

        return (edges.size() == n)?ans + 2: ans;   
    }

    long long maxScore3(int n, vector<vector<int>>& edges) {
        // 数学
        // a_n = n^2 - 2n, sum(a_n) + n * (n-1)
        // cycle           sum(a_n) + n * (n-1) + 2 * 1 
        // sum(a_n) + n * (n-1) = 1/3n(n+1)(n+1/2) - n*(n+1) + n*(n-1) + 1
        //                      = （2n^3 + 3n^2 - 11n) / 6 + 1
        long long ans = (2LL * n * n * n + 3LL * n * n - 11 * n)/6 + 1;
        return (edges.size() == n)?ans + 2: ans; 
    }
};