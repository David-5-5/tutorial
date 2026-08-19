#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        int prev = -1, ans = 1, n = seats.size();

        for (int i=0; i<n; i++) {
            if (seats[i] == 1) {
                if (prev == -1) ans = max(ans, i-0);
                else {
                    auto mid = (prev + i) / 2;
                    ans = max(ans, min(mid- prev, i - mid));
                }
                prev = i;
            }
        }

        return max(ans, n - prev - 1);
    }
};