#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - §1.3 双序列配对
// 2026.1.28 复习
class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        // 自行解答
        unordered_map<int, int> cnt_all, cnt_1;
        int n = basket1.size();
        

        for (int i=0; i<n; ++i) {
            cnt_all[basket1[i]] ++; cnt_all[basket2[i]] ++;
            cnt_1[basket1[i]] ++;
        }

        vector<int> arr_chg; int mn = INT_MAX;
        for (auto [k, c]: cnt_all) {
            mn = min(mn, k);
            if (c % 2) return -1;
            if (cnt_1.count(k)) {
                arr_chg.insert(arr_chg.end(), abs(cnt_1[k] - c/2), k);
            } else {
                arr_chg.insert(arr_chg.end(), c/2, k);
            }
        }
        
        sort(arr_chg.begin(), arr_chg.end());

        long long ans = 0;                          
        for (int i=0; i<arr_chg.size()/2; ++i) {    // 两两交换，取小的值作为成本
            // 当发现 mn * 2 <= arr_chg[i] 中断循环时，性能未提升
            ans += min(mn * 2, arr_chg[i]);         // 关键，可以通过数组中最小值两次交换
        }   
        return ans;
    }
};