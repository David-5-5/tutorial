#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.1 堆 - 基础
class Solution {
public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        // 自行解答
        priority_queue<pair<int,int>, vector<pair<int,int>>, less<>> buys;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> sells;

        for (auto o: orders) {
            int price = o[0], amount = o[1], type = o[2];
            if (type == 0) {        // buy
                while (sells.size() && sells.top().first <= price && amount) {
                    auto [prc, amt] = sells.top(); sells.pop();
                    if (amount < amt) sells.emplace(prc, amt-amount);
                    amount = max(0, amount - amt);
                }
                if (amount) buys.emplace(price, amount);
            }else {
                while (buys.size() && buys.top().first >= price && amount) {
                    auto [prc, amt] = buys.top(); buys.pop();
                    if (amount < amt) buys.emplace(prc, amt-amount);                    
                    amount = max(0, amount - amt);
                }
                if (amount) sells.emplace(price, amount);
            }
        }
        const int mod = 1e9 + 7;
        int ans = 0;
        while (!buys.empty()) {
            cout << buys.top().second << endl;
            ans = (ans + buys.top().second) % mod; buys.pop();
        }
        while (!sells.empty()) {
            cout << sells.top().second << endl;
            ans = (ans + sells.top().second) % mod; sells.pop();
        }
        return ans; 
    }
};