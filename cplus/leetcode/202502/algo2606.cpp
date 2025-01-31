#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最大子数组和
class Solution {
public:
    int maximumCostSubstring(string s, string chars, vector<int>& vals) {
        // 自行解答，类似于 53
        vector<int> ch_val(26);
        for (int i=0; i<26; i++) ch_val[i] = i+1;
        for (int i=0; i<chars.size(); i++) {
            ch_val[chars[i]-'a'] = vals[i];
        }

        int sum = 0, ans = 0;
        for (auto& ch : s) {
            sum += ch_val[ch-'a'];
            if (sum < 0) sum = 0;
            ans = max(ans, sum);
        }
        return ans;      

    }
};