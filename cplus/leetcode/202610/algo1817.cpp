#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findingUsersActiveMinutes(vector<vector<int>>& logs, int k) {
        unordered_map<int, set<int>> actives;
        for (auto& l: logs) {
            actives[l[0]].insert(l[1]);
        }

        vector<int> ans(k);

        for (auto &[_, cnt]: actives) {
            if (cnt.size() <= k) {
                ans[cnt.size()-1] ++;
            }
        }
        return ans;
    }
};