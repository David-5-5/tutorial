#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 数学贪心 - 基础
class Solution {
public:
    int minCostToMoveChips(vector<int>& position) {
        // 自行解答
        int odd = 0, even = 0;

        for (int p : position)
            if (p % 2) odd ++;
            else even ++;
        
        return min(odd, even);
    
    }
};