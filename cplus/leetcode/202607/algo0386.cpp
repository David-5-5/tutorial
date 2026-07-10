#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> ans = {}; int cur = 1;
        while (ans.size() < n) {
            ans.emplace_back(cur);
            while (cur * 10 <= n) {
                cur *= 10;
                ans.emplace_back(cur);
            }
            while (cur >= n || cur % 10 == 9 ) cur /= 10;
            cur ++;
        }

        return ans;
    }
};