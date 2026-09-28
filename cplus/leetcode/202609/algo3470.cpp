#include <bits/stdc++.h>
using namespace std;

vector<long long> pres = {1};
auto init = [] {
    int i = 1;
    while (pres.back() < 1e16) {
        pres.emplace_back(pres.back() * i);
        pres.emplace_back(pres.back() * i);
        i ++;
    }
    return 0;
}();

class Solution {
public:
    vector<int> permute(int n, long long k) {
        vector<int> ans;
        
        // n 很大对情况下，全排列的数量远大于 k<= 1e16，
        // 这种情况下，按顺序填写 1, 2, 3, ... 即可
        if (n < pres.size() && k > pres[n] * (2-n%2)) return {};
        
        vector cand(2, vector<int>());
        for (int i=1; i<=n; i++) cand[i%2].emplace_back(i);

        int parity = 1;
        k -= 1;

        for (int i=0; i<n; i++) {
            int j;
            if (n-1-i < pres.size()) {
                j = k / pres[n-1-i];
                k = k % pres[n-1-i];
                if (n % 2 == 0 && i == 0) {
                    parity = (j + 1) % 2;
                    j /= 2;
                }
            } else j = 0;
            ans.emplace_back(cand[parity][j]);
            cand[parity].erase(cand[parity].begin() + j);
            parity ^= 1;
        }
        return ans;
    }
};