#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> smallestK(vector<int>& arr, int k) {
        sort(arr.begin(), arr.end());

        return vector<int>(arr.begin(), arr.begin() + k);
    }
};