#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.1 深度优先搜索（DFS）
class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        // 题目太罗嗦
        int n = status.size();
        vector<int> hasKeys = status;
        vector<bool> hasBoxs(n); 
        for (auto& b: initialBoxes) hasBoxs[b] = true;

        int ans = 0;
        auto dfs = [&](this auto && dfs, int x) -> void {
            ans += candies[x];
            hasBoxs[x] = false;     // 已经使用
            for (auto& y: containedBoxes[x]) {
                hasBoxs[y] = true;
                if (hasKeys[y]) dfs(y);
            }
            for (auto& y: keys[x]) {
                hasKeys[y] = true;
                if (hasBoxs[y]) dfs(y);
            }

        };

        for (auto b: initialBoxes) {
            if (hasKeys[b] && hasBoxs[b]) dfs(b);
        }

        return ans; 
    }
};