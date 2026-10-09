#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> peopleIndexes(vector<vector<string>>& favoriteCompanies) {
        set<int> cand; unordered_map<string, int> comp_id;
        vector<set<int>> favs; int n = favoriteCompanies.size();
        int idx[n];
        iota(idx, idx+n, 0);
        sort(idx, idx + n, [&](int i, int j) {
            return favoriteCompanies[i].size() > favoriteCompanies[j].size();
        });

        for (int i=0; i<n; i++) {
            auto & fc = favoriteCompanies[idx[i]];
            set<int> favorite;
            for (auto & comp: fc) {
                if (!comp_id.count(comp)) {
                    comp_id[comp] = comp_id.size();
                }
                favorite.emplace(comp_id[comp]);
            }
            
            bool found = false;
            for (int j=0; j<favs.size() && !found; j++) {
                auto & compare = favs[j];

                auto it1 = favorite.begin(), it2 = compare.begin();
                while (it1 != favorite.end() && it2 != compare.end()) {
                    if (*it1 == *it2) {
                        it1 ++; it2 ++;
                    } else if (*it1 > *it2) {
                        it2 ++;
                    } else break;
                }
                if (it1 == favorite.end()) found = true; 
            }
            if (!found) cand.emplace(idx[i]);
            favs.emplace_back(favorite);
        }

        return vector<int>(cand.begin(), cand.end());  
    }
};