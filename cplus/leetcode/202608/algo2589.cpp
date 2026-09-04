#include <bits/stdc++.h>
using namespace std;

// 复习
class Solution {
public:
    int findMinimumTime(vector<vector<int>>& tasks) {
        // tuple : start, end, prefix sum of duration
        vector<tuple<int, int, int>> turnon;

        turnon.emplace_back(-1, -1, 0);

        sort(tasks.begin(), tasks.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        
        for (auto& task: tasks) {
            auto start = task[0], end = task[1], duration = task[2];
            auto it = lower_bound(turnon.begin(), turnon.end(), start, [](const tuple<int,int,int> & t, int val){
                return get<0>(t) < val;
            }) - 1;
            
            //    start                                    end
            //    [                                          ]
            //  [            ]   [     ] [     ] [     ] 
            //  *it
            //                  | -- 区间 duration --     | 
            //     | r -start |
            duration -= get<2>(turnon.back()) - get<2>(*it);   // 区间 duration
            if (start <= get<1>(*it)) duration -= get<1>(*it) - start + 1; // r - start
            if (duration <= 0) continue;

            auto pred = get<2>(turnon.back()) + duration;
            auto ns = end - duration + 1;
            while (get<1>(turnon.back()) >= ns) {
                ns -= get<1>(turnon.back()) - get<0>(turnon.back()) + 1;
                turnon.pop_back();
            }
            turnon.emplace_back(ns, end, pred);
        }

        return get<2>(turnon.back());
    }
};