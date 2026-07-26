#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        int n = wall.size(), mx = 0;
        unordered_map<long long, int> slot;
        for (auto row: wall) {
            int m = row.size(); long long right = 0;
            for (int i=0; i<m-1; i++) {
                right += row[i];
                slot[right] ++;
                mx = max(slot[right], mx);
            }
        }
        
        return n - mx;
    }
};