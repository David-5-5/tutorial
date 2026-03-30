#include <bits/stdc++.h>
using namespace std;

// 字符串 - 四、字符串哈希
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        // 暴力搜索
        unordered_map<string, int> cnt;
        int n = s.length();
        for (int i=0; i<n-9; i++) {
            cnt[s.substr(i, 10)] ++;
        }

        vector<string> ans;
        for (auto &[k, v]: cnt) if (v>1) ans.emplace_back(k);
        return ans;
    }

    vector<string> findRepeatedDnaSequences(string s) {
        // 'A' : 0, 'C': 1, 'G': 2 和 'T : 3
        // each char 2bit 20 bit
        unordered_map<char, int> bin = {{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};
        const int mask = (1 << 20) - 1;
        unordered_map<int, int> cnt;
        vector<string> ans;
        int cur = 0, L = 10, n = s.length();

        for (int i=0; i<L-1; i++) {
            cur = (cur << 2) | bin[s[i]];
        }
        for (int i=L-1; i<n; ++i) {
            cur = ((cur << 2) | bin[s[i]]) & mask;
            cnt[cur] += 1;
            if (cnt[cur] == 2) ans.emplace_back(s.substr(i-L+1, L));
        }
        return ans;
    }

};