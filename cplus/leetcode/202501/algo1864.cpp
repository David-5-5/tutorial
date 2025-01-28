#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 其他
class Solution {
public:
    int minSwaps(string s) {
        int cnt = 0, ans = -1;
        for (auto ch : s) if (ch == '1') cnt++;

        if (cnt * 2 == s.size()) {
            string target = "";
            int move = 0;
            for (int i=0; i<cnt; i++) target += "01";
            for (int i=0; i<s.size(); i++) if (s[i] != target[i]) move++;
            ans = move / 2;

            target = "", move = 0; // 恢复
            for (int i=0; i<cnt; i++) target += "10";
            for (int i=0; i<s.size(); i++) if (s[i] != target[i]) move++;
            ans = min(ans, move / 2);
        } else if (cnt * 2 == s.size() + 1) {
            string target = "1";
            int move = 0;
            for (int i=0; i<cnt-1; i++) target += "01";
            for (int i=0; i<s.size(); i++) if (s[i] != target[i]) move++;
            ans = move / 2;
        } else if (cnt * 2 == s.size() - 1) {
            string target = "0";
            int move = 0;
            for (int i=0; i<cnt; i++) target += "10";
            for (int i=0; i<s.size(); i++) if (s[i] != target[i]) move++;
            ans = move / 2;
        }

        return ans;
    }
};