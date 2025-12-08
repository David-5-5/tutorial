#include <bits/stdc++.h>
using namespace std;

// 字符串 - 一、KMP
class Solution {
public:
    bool canChoose(vector<vector<int>>& groups, vector<int>& nums) {
        // 暴力
        int n = groups.size(), m = nums.size();

        auto find = [&](int i, int j) -> int {
            while (j + groups[i].size() <= m) {
                bool find = true;
                for (int x=0; x<groups[i].size(); ++x) {
                    if (groups[i][x] != nums[j+x]) {find=false; break;}
                }
                if (find) return j + groups[i].size();
                else j++;
            }
            return -1;
        };

        int j = 0;
        for (int i = 0; i<n; ++i) {
            j = find(i, j);
            if (j == -1) return false;
        }

        return true;     
    }
};