#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        // k = i - j    - (n-1) <= k <= m-1 
        // i = k + j   k <= i < k + n 结合 0 <= i < m
        // max(k, 0) <= i < min(k+n, m)
        for (int k=-n+1; k<m; k++) {
            vector<int> arr;
            for (int i=max(k, 0); i<min(k+n, m); i++) {
                arr.push_back(mat[i][i-k]);
            }
            sort(arr.begin(), arr.end());
            for (int i=max(k, 0); i<min(k+n, m); i++) {
                mat[i][i-k] = arr[i-max(k, 0)];
            }
        }

        return mat;
    }
};