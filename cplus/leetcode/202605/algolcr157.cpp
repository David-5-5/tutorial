#include <bits/stdc++.h>
using namespace std;

// LCR series
class Solution {
public:
    vector<string> goodsOrder(string goods) {
        vector<string> res;
        sort(goods.begin(), goods.end());
        do {
            res.push_back(goods);
        } while (next_permutation(goods.begin(), goods.end()));
        return res;
    }
};