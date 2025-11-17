#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 四、双序列双指针 - 4.2 判断子序列
class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        // 自行解答
        sort(strs.begin(), strs.end(), [](const string& a, const string& b) {
            return a.length() > b.length();
        });

        int n = strs.size();
        for (int i=0; i<n; ++i) {
            int cnt = 0;
            for (int j=0; j<n; ++j) {
                if (i == j) continue;
                int inx1 = 0, inx2 = 0; 
                while (inx1<strs[i].length() && inx2<strs[j].length()) {
                    if (strs[i][inx1] == strs[j][inx2]) inx1 ++;
                    inx2 ++;
                }
                if (inx1 != strs[i].length()) cnt += 1;
                
            }
            if (cnt == n-1) return strs[i].length();
        }
        return -1;
    }
};