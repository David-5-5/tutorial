#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 4.1 队列 - 基础
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        // 自行解答
        sort(deck.rbegin(), deck.rend());

        deque<int> ans;
        for (auto& v: deck) {
            if (ans.size() > 1) {
                int b = ans.back();
                ans.pop_back();
                ans.push_front(b);
            }
            ans.push_front(v);
        }

        return vector<int>(ans.begin(), ans.end());  
    }
};