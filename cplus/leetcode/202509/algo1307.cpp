#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.5 排列型回溯
class Solution {
public:
    bool isSolvable(vector<string>& words, string result) {
        // 自行解答, 超时
        unordered_map<char, int> chars; unordered_set<char> initial;
        for (auto& w : words) for (auto& ch: w) if (!chars.count(ch)) chars[ch]=chars.size();
        for (auto & ch:result) if (!chars.count(ch)) chars[ch]=chars.size();
        initial.insert(result[0]); for (auto& w:words) initial.insert(w[0]);
        
        int n = chars.size();
        vector<char> v_chars(n); for (auto& [k,v]:chars) v_chars[v] = k;
        vector<int> mapto(n);

        auto check = [&] ()-> bool {
            int left = 0;
            for (auto& w: words) {
                int cur = 0;
                for (auto ch: w) {
                    cur = cur * 10 + mapto[chars[ch]];
                }
                left += cur;
            }
            int right = 0;
            for (auto ch: result) {
                right = right * 10 + mapto[chars[ch]];
            }
            return left == right;
        };

        auto dfs = [&] (this auto&& dfs, int i, int mask) -> bool {
            if (i == n) return check();

            for (int k=0; k<10; ++k) {
                if (initial.count(v_chars[i]) && k==0) continue; // 无前导 0
                if (((mask >> k)&1) == 0) {
                    mapto[i] = k;
                    if (dfs(i+1, mask|1<<k)) 
                        return true;
                    // mapto[i] = 0;   // 恢复现场
                }
            }

            return false;

        };

        return dfs(0, 0);
    }


};