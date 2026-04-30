#include <bits/stdc++.h>
using namespace std;

// 视频 - 二分
class Solution {
public:
    int maxPossibleScore(vector<int>& start, int d) {
        // 二分
        sort(start.begin(), start.end());
        int n = start.size();

        auto check = [&](int len) -> bool {
            long long pos = 0;
            for (int i=0; i<n; i++) {
                if (pos > start[i] + d) return false;
                pos = max(pos, (long long)start[i]) + len;
            }
            return true;
        };

        long long l = 0, r = start[n-1] + d + 1;
        while (l + 1 < r) {
            auto m = (l + r) / 2;
            (check(m)? l : r) = m;
        }
        return l;
    }
};