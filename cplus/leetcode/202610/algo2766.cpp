#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> relocateMarbles(vector<int>& nums, vector<int>& moveFrom, vector<int>& moveTo) {
        set<int> stone(nums.begin(), nums.end()); int n = moveFrom.size();

        for (int i=0; i<n; i++) {
            stone.erase(moveFrom[i]);
            stone.insert(moveTo[i]);
        }

        return vector<int>(stone.begin(), stone.end());
    }
};