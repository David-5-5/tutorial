#include <bits/stdc++.h>
using namespace std;

// 位运算 - 基础题
class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        long a = 0, b = 0; int n = A.size();
        vector<int> ans;
        for (int i=0; i<n; ++i){
            a |= (long)1 << A[i]; 
            b |= (long)1 << B[i];
            ans.push_back(__builtin_popcountl(a & b));
            // ans.push_back(popcount(a & b));
        }
        return ans;       
    }
};