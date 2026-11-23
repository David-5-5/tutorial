#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int pres = 0; unordered_set<int> rems;  // prior to set<int>

        for (auto & v : nums) {
            int curs = pres + v;
            if (rems.count(curs % k)) return true;
            rems.emplace(pres % k);
            pres = curs;
        }

        return false;
    }
};