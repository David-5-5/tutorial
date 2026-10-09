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

    int minDays2(vector<int>& bloomDay, int m, int k) {
        // merge intervals
        if (bloomDay.size() < 1LL * m * k) return -1;
        map<int, int> intervals; int n = bloomDay.size();
        int idx[n];
        iota(idx, idx+n, 0);
        sort(idx, idx + n, [&](int i, int j) {
            return bloomDay[i] < bloomDay[j];
        }); 
        
        int ans = 0;
        for (int i=0; i<n; i++) {
            auto x = idx[i];
            
            auto x_val = x;
            auto right = intervals.lower_bound(x+1);
            if (right!=intervals.end() && right->first == x + 1) {
                x_val = right->second;
                ans -= (right->second - right->first+1) / k;
                intervals.erase(right);
            }
            
            auto left = intervals.upper_bound(x);
            if (left != intervals.begin()) left --;
            if (left != intervals.end() && left->second + 1 == x) {
                ans -= (left->second - left->first+1) / k;
                left->second = x_val;
                ans += (left->second - left->first+1) / k;
            } else {
                intervals[x] = x_val;
                ans += (x_val - x + 1) / k;
            }

            if (ans >= m) return bloomDay[x];
        }

        return -1;    
    }

};

int main() {
    vector<int> bloomDay = {7,7,7,7,12,7,7};
    cout << Solution().minDays2(bloomDay, 2, 3) << endl;
}