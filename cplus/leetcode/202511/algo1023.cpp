#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 四、双序列双指针 - 4.2 判断子序列
class Solution {
public:
    vector<bool> camelMatch(vector<string>& queries, string pattern) {
        // 复习，简化实现，不需要 dp
        int n = pattern.length(); vector<bool> ans;
        for (const auto& q: queries) {
            int m = q.length(), inx1 = 0, inx2 = 0;
            while (inx1 < m && inx2 < n) {
                if (q[inx1] == pattern[inx2]) {
                    inx1 ++; inx2 ++;
                } else if (islower(q[inx1])) inx1 ++;
                else break;
            }
            if (inx1 == m && inx2 == n) ans.push_back(true);
            else if (inx2 == n) {
                bool has_upper = false;
                for (int i = inx1; i<m; i++) 
                    if (isupper(q[i])) {has_upper == true; break;}
                ans.push_back(has_upper == false);
            }
        }
        return ans;
        
    }
};