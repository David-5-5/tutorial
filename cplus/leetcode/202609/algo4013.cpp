#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> countTasks(vector<int>& tasks, vector<int>& shifts) {
        int n = tasks.size(); vector<int> ans;
        vector<long long> pres_t(tasks.begin(), tasks.end());
        for (int i=1; i<n; i++) pres_t[i] += pres_t[i-1];

        long long pres = 0;
        for (auto v: shifts) {
            auto it = upper_bound(pres_t.begin(), pres_t.end(), pres + v);
            if (it == pres_t.end()) pres = 0;
            else pres += v;
            ans.emplace_back(pres_t.end() - it);
        }
        return ans;
    }
};