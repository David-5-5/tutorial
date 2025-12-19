#include <bits/stdc++.h>
using namespace std;

// 九、子序列自动机
class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        // 参考题解
        vector pos(26, vector<int>());

        for (int i=0; i<s.length(); i++) pos[s[i]-'a'].emplace_back(i);

        int ans = 0;
        for (auto& word : words) {
            bool satisfied = true; int start = -1;
            for (auto & ch : word) {
                auto it = ranges::upper_bound(pos[ch-'a'], start);
                if (it != pos[ch-'a'].end()){
                    start = *it;
                } else {
                    satisfied = false; break;
                }
            }
            if (satisfied) ans ++;
        }

        return ans;     
    }
};