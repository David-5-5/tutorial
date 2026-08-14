#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int n) {
        vector<int> arr(256, -1); int val = 0;
        for (int i=0; i<8; i++) if (cells[i]) val |= 1 << i;

        int p = -1, q = 0; arr[val] = 0;
        while (q < n) {
            q ++; int next = 0;
            for (int i=1; i<7; i++) {
                if (((val >> i - 1) & 1) ^ ((val >> i + 1) & 1) == 0) {
                    next |= 1 << i;
                }
            }
            if (arr[next] >= 0) {p = arr[next]; break;}
            else arr[next] = q;
            val = next;
        }

        if (p != -1)  {
            int mod = p - q;
            q = (n - p) % mod + p;
        }

        vector<int> ans(8);
        for (int i=0; i<256; i++) if (arr[i] == q) {
            for (int j=1; j<7; j++) {
                ans[j] = (i >> j) & 1;
            }
            break;
        };

        return ans;
    }
};