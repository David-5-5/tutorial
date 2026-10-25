#include <bits/stdc++.h>
using namespace std;

class RangeFreqQuery {
private:
    unordered_map<int, vector<int>> val_idx;
public:
    RangeFreqQuery(vector<int>& arr) {
        for (int i=0; i<arr.size(); i++) {
            val_idx[arr[i]].emplace_back(i);
        }
    }
    
    int query(int left, int right, int value) {
        auto l = lower_bound(val_idx[value].begin(), val_idx[value].end(), left);
        auto r = upper_bound(val_idx[value].begin(), val_idx[value].end(), right);
        return r - l;
    }
};

/**
 * Your RangeFreqQuery object will be instantiated and called as such:
 * RangeFreqQuery* obj = new RangeFreqQuery(arr);
 * int param_1 = obj->query(left,right,value);
 */