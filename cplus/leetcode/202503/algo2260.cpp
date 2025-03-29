#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.1 枚举右，维护左
class Solution {
public:
    int minimumCardPickup(vector<int>& cards) {
        // 自行解答
        int n = cards.size(), ans = INT_MAX;
        unordered_map<int, int> pos;

        for (int i=0; i<n; i++) {
            if (pos.count(cards[i])) ans = min(ans, i-pos[cards[i]]+1);

            pos[cards[i]] = i;
        }

        return ans < INT_MAX? ans : -1;  
    }
};