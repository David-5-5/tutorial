#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int bestSeqAtIndex(vector<int>& height, vector<int>& weight) {
        // 同 354
        vector<pair<int, int>> actors;
        for (int i=0; i<height.size(); i++) {
            actors.emplace_back(height[i], weight[i]);
        }

        sort(actors.begin(), actors.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first == b.first) return (a.second > b.second);
            return a.first < b.first;
        });

        vector<int> arr;

        for (auto &[_, w]: actors) {
            auto it = lower_bound(arr.begin(), arr.end(), w);
            if (it == arr.end()) {
                arr.emplace_back(w);
            } else *it = w;
        }

        return arr.size();

    }
}; 