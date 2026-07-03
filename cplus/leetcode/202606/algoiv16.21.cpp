#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findSwapValues(vector<int>& array1, vector<int>& array2) {
        int diff = accumulate(array1.begin(), array1.end(), 0LL) - 
            accumulate(array2.begin(), array2.end(), 0LL);
        
        if (diff % 2) return {};
        else diff /= 2;

        unordered_set hash(array1.begin(), array1.end());

        for (auto v: array2) if (hash.count(v+diff)) return {v+diff, v};

        return {};
    }
};