#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canRemoveAll(vector<int>& types, vector<int>& colors, vector<int>& groupSize) {
        stack<tuple<int, int, int>> st; int n = types.size();
        for (int i=0; i<n; i++) {
            auto & t = types[i], & c = colors[i];
            if (st.empty()) {
                if (groupSize[t] > 1) st.emplace(t, c, 1);
            } else {
                auto &[tt, tc, cnt] = st.top();
                if (t == tt && c == tc) {
                    cnt += 1;
                    if (cnt == groupSize[t]) st.pop();
                }
                else if (groupSize[t] > 1)st.emplace(t, c, 1);
            }
        }
        return st.empty();     
    }
};