#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 专题：跳跃游戏
class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        // 自行解答 - 广度优先搜索
        int n = arr.size(), vis[n];
        memset(vis, 0, sizeof(vis));
        vector<int> q;
        q.push_back(start); vis[start] = 1;
        while (q.size()) {
            vector<int> nxt;
            for (auto& v: q) {
                if (arr[v] == 0) return true;
                vector<int> jmp = {v-arr[v], v+arr[v]};
                for (auto& j : jmp) {
                    if (j >= 0 && j <n && !vis[j]) {
                        nxt.push_back(j); vis[j] = 1;
                    }
                }
            }
            q = move(nxt);
        }
        return false;        
    }
};