#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int l = -1, r = m * n;
        while (l + 1 < r) {
            auto mid = (l + r) / 2;
            auto x = mid / n, y = mid % n;
            if (target < matrix[x][y]) 
                r = mid;
            else if (target == matrix[x][y])
                return true;
            else l = mid;
        }

        return false;    
    }
};