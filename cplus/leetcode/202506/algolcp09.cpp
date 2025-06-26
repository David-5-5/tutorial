#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 专题：跳跃游戏
class Solution {
public:
    int minJump(vector<int>& jump) {
        // 自行解答
        int left = 0, step = 0, cur = 0, n = jump.size();
        vector<int> q;
        vector<bool> vis(n);
        q.emplace_back(0); vis[0] = true;
        while (q.size()) {
            step ++;
            vector<int> nxt;
            int mx_left = 0;
            for (auto& pos : q) {
                if (pos + jump[pos] >= n) return step;
                // 向左跳
                if (!vis[pos+jump[pos]]) {
                    nxt.emplace_back(pos + jump[pos]);
                    vis[pos+jump[pos]] = true;
                }
                // 向右跳
                mx_left = max(pos, mx_left);    // 记住本次的最大值
            }
            q = move(nxt);
            for (int i = left+1; i<mx_left; i++) {  // 将本次向右跳加入队列
                if (!vis[i]) {q.emplace_back(i); vis[i] = true;}                
            }
            left = mx_left;                    // 更新left，避免重复计算
        }
        return -1;
    }
};