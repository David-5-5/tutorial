#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 专题：把 X 变成 Y
class Solution {
public:
    int minimumOperations(vector<int>& nums, int start, int goal) {
        // 参考题解 广度优先搜索
        auto op1 = [](int x, int y) -> int {return x+y;};
        auto op2 = [](int x, int y) -> int {return x-y;};
        auto op3 = [](int x, int y) -> int {return x^y;};
        vector<function<int(int,int)>> ops = {op1, op2, op3};

        vector<int> q; q.push_back(start);
        vector<bool> vis(1001); vis[start] = true;
        int depth = 0;
        while (q.size()) {
            depth ++;
            vector<int> nxt;
            for (auto u: q) for (auto v:nums) {
                for (auto op : ops) {
                    auto val = op(u, v);
                    if (val == goal) return depth;
                    else if (val >=0 && val <= 1000 && !vis[val]) {
                        nxt.push_back(val);
                        vis[val] = true;
                    }
                }
            }
            q = move(nxt);
        }
        
        return -1;

    }
};