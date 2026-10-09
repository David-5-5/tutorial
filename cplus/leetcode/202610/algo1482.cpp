#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        // binary search
        int mx = ranges::max(bloomDay);
        if (bloomDay.size() < 1LL * m * k) return -1;
        auto check = [&](int limit) -> bool {
            int res = 0, seg = 0;
            for (auto & d: bloomDay) {
                if (d <= limit) seg ++;
                else {
                    res += seg / k; seg = 0;
                }
            }
            res += seg / k;
            return res >= m;
        };
        
        int l = 0, r = mx + 1;
        while (l + 1 < r) {
            auto mid = (l + r) / 2;
            (check(mid)?r:l) = mid;
        }
        return r;
    }


};

int main() {
    vector<int> bloomDay = {7,7,7,7,12,7,7};
    cout << Solution().minDays2(bloomDay, 2, 3) << endl;
}