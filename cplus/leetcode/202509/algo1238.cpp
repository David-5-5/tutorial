#include <bits/stdc++.h>
using namespace std;

// 位运算 - 其他
class Solution {
public:
    vector<int> circularPermutation(int n, int start) {
        // 用格雷码公式构造 g_i = i ^ (i/2)
        vector<int> ans; int pos;
        for (int i=0; i<(1<<n); ++i) {
            ans.push_back( i ^ (i/2));
            if (ans.back() == start) pos = ans.size();
        }
        if (pos)rotate(ans.begin(), ans.begin()+pos-1, ans.end());
        return ans;
    }
};