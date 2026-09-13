#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        vector<int> cnt(n+1);
        for (auto & c: citations) {
            cnt[min(c, n)] ++;
        }

        int h = 0;
        for (int i=n; i>=0; i--) {
            h += cnt[i];
            if (h >= i) return i;
        }

        return 0;
    }
};