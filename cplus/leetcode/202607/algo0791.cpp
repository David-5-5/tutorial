#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string customSortString(string order, string s) {
        // 自行解答 自定义排序规则
        unordered_map<char, int> chInx;
        for (int i=0; i<order.length(); i++) chInx[order[i]] = i;
        sort(s.begin(), s.end(), [&](const char a, const char b) {
            return chInx[a] < chInx[b];
        });

        return s;
    }
};