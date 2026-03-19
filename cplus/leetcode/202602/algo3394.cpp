#include <bits/stdc++.h>
using namespace std;

// 二、区间贪心 - 2.5 合并区间
class Solution {
public:
    bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
        // 自行解答
        auto merge = [&] (vector<pair<int, int>>& intervals) -> int {
            sort(intervals.begin(), intervals.end(), [](const pair<int,int> a, const pair<int, int> b) {
                return a.second < b.second; // sort by right
            });

            stack<pair<int, int>> st; int right = -1;
            for (auto &[l, r] : intervals) {
                while (!st.empty() && st.top().second > l) {
                    l = min(l, st.top().first); st.pop();
                }

                st.emplace(l, r);
            }
            
            return st.size();
        };

        vector<pair<int, int>> x_intv, y_intv;
        for (int i=0; i<rectangles.size(); ++i) {
            auto& p = rectangles[i];
            x_intv.emplace_back(p[0], p[2]);
            y_intv.emplace_back(p[1], p[3]);
        }
        return merge(x_intv) > 2 || merge(y_intv) > 2;
    }
};