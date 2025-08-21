#include <bits/stdc++.h>
using namespace std;


// 二叉树 - 2.16 其他
class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
        vector<int> d_first;
        for (int i=1; i<=20; i++) d_first.push_back((1<<i)-1);

        vector<int> ans;
        int d = ranges::lower_bound(d_first, label)-d_first.begin();

        auto actual = label;
        if (d%2) actual = d_first[d-1] + 1 + (d_first[d]-label);

        for (int i=d; i; --i) {
            label = actual;
            if (i%2) label = d_first[i-1] + 1 + (d_first[i]-actual);
            ans.push_back(label);
            actual = actual >> 1;
        }
        ans.push_back(1);
        reverse(ans.begin(), ans.end()); return ans;
    }
};