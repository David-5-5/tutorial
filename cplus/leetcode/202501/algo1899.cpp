#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 其他
class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        int mask = 0;
        for (int i=0; i<triplets.size(); i++) {
            if (triplets[i][0] <= target[0] && triplets[i][1] <= target[1] && triplets[i][2] <= target[2]) 
                for (int j=0; j<3; j++) 
                    if (triplets[i][j] == target[j]) mask |= 1 << j;

            if (mask == 7) return true;
        }

        return false;     
    }
};