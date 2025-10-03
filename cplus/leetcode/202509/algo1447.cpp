#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.8 互质
class Solution {
public:
    vector<string> simplifiedFractions(int n) {
        // 自行解答
        vector<string> ans;
        for (int i=1; i<n; ++i) for (int j=i+1; j<=n; ++j)  {
            if (gcd(i, j) == 1)  {
                ans.push_back(to_string(i) + "/" + to_string(j));
            }
        }
        return ans;
    }
};