#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        // 自行解答 二分 （是不是有贪心的做法？）
        int m = nums.size(), n = changeIndices.size();

        auto check = [&](int k) -> bool {
            vector<int> last(m, -1);
            for (int i=0; i<k; i++) {
                last[changeIndices[i]-1] = i;
            }
            int idx[m];
            iota(idx, idx+m, 0);
            sort(idx, idx + m, [&](int i, int j) {
                return last[i] < last[j];
            });
            if (last[idx[0]] < 0) return false;

            int used = 0;
            for (int i=0; i<m; i++) {
                int id = idx[i];
                used += 1 + nums[id];
                if (last[id] + 1 < used) return false;
            }
            return true;
        };

        int l = 0, r = n + 1;
        while (l + 1 < r) {
            auto mid = (l + r) / 2;
            (check(mid) ? r : l) = mid;
        }
        return r > n ? -1 : r;            
    }
};