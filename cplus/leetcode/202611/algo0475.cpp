#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        // 二分 + lower_bound upper_bound 查找
        int n = houses.size(), m = heaters.size(); 
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());

        auto check = [&](int radius) -> bool {
            int start = 0;
            for (auto p : heaters) {
                auto l = lower_bound(houses.begin(), houses.end(), p - radius) - houses.begin();
                auto r = upper_bound(houses.begin(), houses.end(), p + radius) - houses.begin();
                if (l > start) return false;
                if (r == n) return true;
                start = r;
            }
            return start == n?true:false;
        };

        int l = -1, r = max(houses.back(),heaters.back()) + 1;
        while (l + 1 < r) {
            auto mid = (l + r) / 2;
            (check(mid)? r : l) = mid;
        }
        return r;
    }

    int findRadius(vector<int>& houses, vector<int>& heaters) {
        // 二分 + 双指针
        int n = houses.size(), m = heaters.size(); 
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());

        auto check = [&](int radius) -> bool {
            int i=0, j=0;
            while (i<n && j<m) {
                if (houses[i] < heaters[j] - radius) return false;
                while (i<n && houses[i] <= heaters[j] + radius) i++;
                j ++;
            }
            return i==n;
        };

        int l = -1, r = max(houses.back(),heaters.back()) + 1;
        while (l + 1 < r) {
            auto mid = (l + r) / 2;
            (check(mid)? r : l) = mid;
        }
        return r;
    }    
};