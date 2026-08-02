#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        unordered_map<string, vector<char>> trans;
        for (auto & a: allowed) {
            trans[a.substr(0, 2)].emplace_back(a[2]);
        }

        int n = bottom.size();
        vector<string> pyramid(n);
        for (int i = 0; i < n - 1; i++) {
            pyramid[i].resize(i + 1);
        }

        pyramid[n-1] = move(bottom);
        unordered_set<string> vis;

        auto dfs = [&](this auto&& dfs, int i, int j) -> bool {
            if (i < 0) return true;

            if (j == pyramid[i].size()) {
                auto row = pyramid[i];
                if (vis.count(row)) return false;
                vis.insert(row);
                return dfs(i-1, 0);
            }

            auto bt = pyramid[i+1].substr(j, 2);

            for (auto ch : trans[bt]) {
                pyramid[i][j] = ch;
                if (dfs(i, j+1)) return true;
            }
            return false;
        };
        
        return dfs(n-2, 0);        


    }
};