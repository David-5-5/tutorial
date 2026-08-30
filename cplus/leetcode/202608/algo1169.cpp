#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> invalidTransactions(vector<string>& transactions) {
        // 手工完成将字符串按照指定 字符 分组
        auto split = [] (const string &s, char delim) -> vector<string> {
            vector<string> res; string tmp;
            for (char ch : s) {
                if (ch == delim) {
                    res.push_back(tmp); tmp.clear();
                } else {
                    tmp += ch;
                }
            }
            res.push_back(tmp);
            return res;
        };

        vector<vector<string>> all_txs;
        for (auto tx : transactions) all_txs.push_back(split(tx, ','));

        int n = transactions.size(); vector<bool> valid(n, true);

        for (int i=0; i<n; i++) {
            if (!valid[i]) continue;
            if (stoi(all_txs[i][2]) > 1000) {
                valid[i] = false; continue;
            }
            for (int j=0; j<n; j++) {
                if (j == i) continue;
                if (all_txs[i][0] == all_txs[j][0] && all_txs[i][3] != all_txs[j][3] &&
                     abs(stoi(all_txs[i][1]) - stoi(all_txs[j][1])) <= 60){
                    valid[i] = false; valid[j] = false;
                    break;
                }
            }
        }

        vector<string> ans;
        for (int i=0; i<n; i++) if (!valid[i])ans.emplace_back(transactions[i]);
        return ans;
    }
};