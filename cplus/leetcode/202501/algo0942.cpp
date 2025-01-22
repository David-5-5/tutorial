#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 构造题
class Solution {
public:
    vector<int> diStringMatch(string s) {
        // 参考题解，完全蒙了，
        // 贪心 遇到 I 放剩余的最小值，遇到 D 放剩余的最大值
        int mx = s.size(), mn = 0;
        vector<int> ans;
        for (auto ch : s) 
            if (ch == 'I') ans.push_back(mn++);
            else ans.push_back(mx--);
        
        ans.push_back(mn); // last value，now mn == mx
        return ans;
    }
};