#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.1 基础
class Solution {
public:
    long long calculateScore(string s) {
        // 自行解答
        long long ans = 0;
        vector<int> mirror[26];
        int n = s.length();

        for (int i=0; i<n; ++i) {
            int mi = 25 - (s[i] - 'a');
            if (mirror[mi].size()) {
                int j = mirror[mi].back();
                mirror[mi].pop_back();
                ans += i - j;
            } else {
                mirror[s[i] - 'a'].push_back(i);
            }
        }
        return ans;
    }
};