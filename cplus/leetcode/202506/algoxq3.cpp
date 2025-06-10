#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.7 单调栈 - 最小字典序
class Solution {
public:
    vector<int> arrangeBookshelf(vector<int>& order, int limit) {
        unordered_map<int, int> left;
        unordered_map<int, int> select;
        for (auto& o: order) left[o] ++;


        vector<int> ans;
        for (auto& o : order) {
            left[o] --;
            // cout << select.count(o) << endl;
            if (select[o] == limit) continue;

            while (ans.size() && ans.back()> o) {
                if (select[ans.back()]+left[ans.back()] > limit) {
                    select[ans.back()] --;
                    ans.pop_back();
                } else break;
            }
            ans.push_back(o);
            select[o]++;

        }
        
        return ans;
    }
};