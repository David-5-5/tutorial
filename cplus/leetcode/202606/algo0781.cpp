#include <bits/stdc++.h>
using namespace std;

// 贪心 八、其他
class Solution {
public:
    int numRabbits(vector<int>& answers) {
        // 逻辑推理题
        int ans = 0; unordered_map<int, int> grps;
        for (auto & v: answers) {
            if (!grps.count(v) || grps[v] == v + 1) {
                ans += v + 1;
                grps[v] = 1;
            } else {
                grps[v] ++;
            }
        }
        return ans;
    }
};