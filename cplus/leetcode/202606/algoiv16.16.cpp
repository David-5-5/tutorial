#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> subSort(vector<int>& array) {
        if (array.size() <= 1) return {-1, -1};
        int l = array.size(), r = 0, n = array.size();
        vector<int> suf_mn(n, array.back());
        for (int i=array.size()-2; i>=0; i--)  {
            suf_mn[i] = min(suf_mn[i+1], array[i]);
        }

        int pre_mx = array[0];
        for (int i=0; i<n; i++) {
            if (array[i] < pre_mx || array[i] > suf_mn[i]) {
                l = min(l, i); r = max(r, i);
            }
            pre_mx = max(pre_mx, array[i]);
        }
        if (l > r) return {-1, -1};
        return {l, r};
    }
};