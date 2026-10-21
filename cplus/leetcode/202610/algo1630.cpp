#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
        int m = l.size(); vector<bool> ans(m, true);
        for (int i=0; i<m; i++) {
            if (l[i] + 1 < r[i]) {
                vector<int> sub(nums.begin()+l[i], nums.begin()+r[i]+1);
                sort(sub.begin(), sub.end());
                for (int j=2; j<sub.size(); j++) {
                    if (sub[j]-sub[j-1]!=sub[1]-sub[0]) {
                        ans[i] = false; break;
                    }
                }
            }
        }
        return ans;
    }
};