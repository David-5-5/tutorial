#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 专题：跳跃游戏
class Solution {
public:
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        // 参考题解 广度优先搜索
        // 难点 - 确定广度优先搜索的上界 - 技巧对于无上限的广度优先搜索，预估一个上限
        int step = 0, lower = 0, upper = max(*max_element(forbidden.begin(), forbidden.end()) + a, x) + b;
        unordered_set<int> visit;
        unordered_set<int> forbSet(forbidden.begin(), forbidden.end());
        vector<pair<int, int>> que;
        que.emplace_back(0, 1);
        
        while (que.size()) {
            vector<pair<int, int>> nxt;
            for (auto& [pos, dir] : que) {
                if (pos == x) return step;
                // 向前跳
                int newPos = pos + a, newDir = 1;
                if (newPos >= lower && newPos <= upper && !visit.count(newPos) && !forbSet.count(newPos)) {
                    nxt.emplace_back(newPos, newDir); visit.insert(newPos);
                }
                // 向后跳
                if (dir == 1) {
                    newPos = pos - b, newDir = -1;
                    if (newPos >= lower && newPos <= upper && !visit.count(-newPos) && !forbSet.count(newPos)) {
                        nxt.emplace_back(newPos, newDir); visit.insert(-newPos);
                    }
                }
            }
            step ++;
            que = move(nxt);
        }
        return -1;      
    }
};