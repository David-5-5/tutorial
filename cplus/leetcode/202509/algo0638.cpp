#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.7 搜索
class Solution {
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        // 自行解答，有点凑答案
        int mn_cost, cost = 0, n = needs.size();
        for (int i=0; i<n; ++i) cost += price[i] * needs[i];
        mn_cost = cost;
        
        auto check = [&](vector<int> sp, vector<int> need) -> bool {
            int sp_cost = 0;
            for (int i=0; i<n; ++i) {
                if (sp[i]>need[i]) return false;
                sp_cost += sp[i] * price[i];        // 根据题目进行剪枝
            }
            return sp_cost > sp.back();
        };
        

        // 一边遍历 一边删除 
        auto last = remove_if(special.begin(), special.end(), [&](vector<int> sp) {
            return !check(sp, needs);
        });
        special.erase(last, special.end());

        cout << special.size() << endl;
        auto dfs = [&](this auto dfs, int cost) -> void {
            mn_cost = min(mn_cost, cost);

            for (int i=0; i<special.size(); ++i) {
                if (check(special[i], needs)) {
                    int sp_cost = 0;
                    for (int j=0; j<n; ++j) {
                        sp_cost += special[i][j] * price[j];
                        needs[j] -= special[i][j];
                    }
                    dfs(cost + special[i].back() - sp_cost);
                    // 恢复现场
                    for (int j=0; j<n; ++j) {
                        needs[j] += special[i][j];
                    }

                }
            }
        };
        dfs(cost); return mn_cost;
    }
};