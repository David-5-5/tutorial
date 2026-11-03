#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string largestWordCount(vector<string>& messages, vector<string>& senders) {
        unordered_map<string, int> msg_cnt; int n = messages.size();

        for (int i=0; i<n; i++) {
            auto & m = messages[i];  int blank = 0;
            for (auto & ch : m) {
                if (ch == ' ') blank ++;
            }
            msg_cnt[senders[i]] += blank + 1;
        }

        string ans; int mx_cnt = 0;
        for (auto &[s, cnt]: msg_cnt) {
            if (cnt > mx_cnt) {
                mx_cnt = cnt; ans = s;
            } else if (cnt == mx_cnt) {
                ans = max(ans, s);
            }
        }
        return ans;
    }
};