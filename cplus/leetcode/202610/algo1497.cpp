#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        vector<int> cnt(k);

        for (auto v: arr) {
            // int r = (v % k + k) % k;
            if (cnt[(k - v % k) % k]) cnt[(k - v % k) % k] --;
            else cnt[(v % k + k) % k] ++;
        }

        if (any_of(cnt.begin(), cnt.end(), [](int a) {
            return a > 0;
        })) return false;
        else return true;

    }
};