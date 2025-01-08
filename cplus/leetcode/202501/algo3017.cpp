#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<long long> countOfPairs(int n, int x, int y) {
        vector<long long> ans(n);

        if (x > y) {
            swap(x, y);
        }

        for (int i=1; i<=n; i++) {
            if (i < (x + y) / 2) {
                int j = (x + y + 1 ) / 2;
                // j < (x + y + 1)/2 距离 [1, j-1] 区间都加 1
                ans[0] += 1;
                ans[j-i] -= 1;
                // (x + y + 1)/2 < j <= y 距离 [x-i+1, x-i+1+y-(j+1)] 区间+1
                ans[abs(x-i)] += 1;
                if (abs(x-i)+y-j < n) ans[abs(x-i)+y-j] -= 1;

                // j > y 时，距离[x-i+2, x-i+n-(y+1)] 区间 +1
                ans[abs(x-i)+1] += 1;
                if (abs(x-i)+n-y < n) ans[abs(x-i)+n-y] -= 1;

            } else{ 
                ans[0] += 1;
                if (n-i+1 < n) ans[n-i+1] -= 1;
            }
        }

        ans[0] *= 2;
        for (int i=1; i<n; i++) {
            ans[i] = ans[i] * 2 + ans[i-1];
        }

        return ans;       
    }
};