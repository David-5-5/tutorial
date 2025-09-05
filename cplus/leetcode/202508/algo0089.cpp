#include <bits/stdc++.h>
using namespace std;

// 位运算 - 其他
class Solution {
public:
    vector<int> grayCode(int n) {
        // 用格雷码公式构造 g_i = i ^ (i/2)
        vector<int> ans;
        for (int i=0; i<(1<<n); ++i) {
            ans.push_back( i ^ (i/2));
        }
        return ans;
    }
};