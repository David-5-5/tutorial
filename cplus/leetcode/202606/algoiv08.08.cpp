#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> permutation(string S) {
        sort(S.begin(), S.end());
        vector<string> res;
        do {
            res.push_back(S);
        } while (next_permutation(S.begin(), S.end())); // 支持重复元素
        return res;
    }
};