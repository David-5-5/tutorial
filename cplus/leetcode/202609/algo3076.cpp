#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> shortestSubstrings(vector<string>& arr) {
        int n = arr.size();

        auto check = [&](int i, string & sub) {
            for (int j = 0; j<n; j++) {
                if (i != j && arr[j].find(sub) != string::npos) return false;
            }

            return true;
        };

        vector<string> ans(n);
        for (int i=0; i<n; i++) {
            int m = arr[i].length();
            string res;
            for (int size = 1; size <= m && res.empty(); size++) {
                for (int j=size; j<=m; j++) {
                    string t = arr[i].substr(j-size, size);
                    if ((res.empty() || t < res) && check(i, t)) {
                        res = t;
                    }
                }
            }
            ans[i] = res;
        }

        return ans;    

    }
};