#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 数学贪心 - 基础
class Solution {
public:
    int minimumRounds(vector<int>& tasks) {
        // 自行解答
        // unordered_map is priority to map
        unordered_map<int, int> cnt; 
        for (int t : tasks)
            cnt[t] += 1;
        
        int ans = 0;
        for (auto it=cnt.begin(); it!=cnt.end(); ++it) {
            if (it->second == 1) return -1;
            ans += (it->second + 2) / 3; // 上取整
        }

        return ans;
    }

    int minimumRounds2(vector<int>& tasks) {
        // 参考题解
        // unordered_map is priority to map
        unordered_map<int, int> cnt; 
        for (int t : tasks)
            cnt[t] += 1;
        
        int ans = 0;
        // 另一种遍历 map 的写法
        for (auto& [_, c]: cnt) {
            if (c==1) return -1;
            ans += (c+2) / 3;   // 上取整
        }

        return ans;
    }
};