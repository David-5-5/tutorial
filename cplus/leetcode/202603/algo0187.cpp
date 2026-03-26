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


};