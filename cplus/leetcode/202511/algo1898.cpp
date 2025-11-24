#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 四、双序列双指针 - 4.2 判断子序列
class Solution {
public:
    int maximumRemovals(string s, string p, vector<int>& removable) {
        // 自行解答
        int n = s.length(), m = p.length();
        int l = -1, r = removable.size() + 1;
        auto check = [&](int mid) -> bool {
            vector<int> prefix(removable.begin(), removable.begin()+mid);
            sort(prefix.begin(), prefix.end());

            int inx1 = 0, inx2 = 0, ptr = 0;
            while (inx1 < n && inx2 < m) {
                if (ptr<mid && inx1 == prefix[ptr]) {
                    ptr ++; inx1 ++; continue;
                }
                if (s[inx1] == p[inx2]) inx2 ++;
                inx1 ++;
            }
            if (inx2 == m) return true;
            else return false;
        };

        while (l + 1 < r) {
            int mid = (l + r) / 2;
            (check(mid)? l : r) = mid;
        }
        return l;        
    }
};