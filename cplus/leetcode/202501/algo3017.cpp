#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<long long> countOfPairs(int n, int x, int y) {
        vector<long long> ans(n);
        if (x > y) {
            swap(x, y);
        }

        // 情况 1：x == y， 情况 2：x+1 == y 直接处理
        if (x + 1 >= y) {
            for (int i = 1; i < n; i++) {
                ans[i - 1] = (n - i) * 2;
            }
            return ans;
        }

        vector<long long> diff(n+1);

        auto add = [&](int l, int r) {
            diff[l] ++;
            diff[r+1] --;
        };

        for (int i=1; i<n; i++) {
            if (i <= x) {
                int j = (x + y + 1 ) / 2;
                // j < (x + y + 1)/2 距离 [1, j-i] 区间都加 1
                add(1, j-i);
                // (x + y + 1)/2 < j <= y 距离 [x-i+1, x-i+1+y-(j+1)] 区间+1
                add(x-i+2, x-i+y-j);
                // j > y 时，距离[x-i+2, x-i+1+n-y] 区间 +1
                add(x-i+1, x-i+n+1-y);
            }else if (i < (x + y) / 2) {
                int j = i + (y - x + 1) / 2;
                add(1, j-i);
                add(i-x+2, i-x+y-j);
                add(i-x+1, i-x+n+1-y);
                // 等价于上面两行代码，差别在于，y 在那个区间
                // add(i-x+1, i-x+y-j); 
                // add(i-x+2, i-x+n+1-y;         
            } else{ 
                add(1, n-i);
            }
        }

        ans[0] = diff[1] * 2;
        for (int i=1; i<n; i++) {
            ans[i] = diff[i+1] * 2 + ans[i-1];
        }
        return ans;
    }
};