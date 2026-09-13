#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int hIndex(vector<int>& citations) {
        // auto check = [&](int mid) -> bool {
        //     auto it = upper_bound(citations.begin(), citations.end(), mid - 1);
        //     if (citations.end() - it >= mid) return true;
        //     else return false;
        // };
        int n = citations.size(), l = 0, r= n+1;
        while (l + 1 < r) {
            auto mid = (l + r) / 2;
            (citations[n-mid]>=mid ? l : r) = mid;
        }
        return l;
    }
};