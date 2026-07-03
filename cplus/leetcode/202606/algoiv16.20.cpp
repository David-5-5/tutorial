#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> getValidT9Words(string num, vector<string>& words) {
        vector<int> l2d = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
        int n = num.size(); vector<string> ans;
        for (auto w: words) {
            bool match = true;
            for (int i=0; i<n; i++) {
                int d = l2d[w[i]-'a'];
                if (num[i]-'0' != d) {
                    match = false; break;
                }
            }
            if (match) ans.emplace_back(w);
        }
        return ans;
    }
};