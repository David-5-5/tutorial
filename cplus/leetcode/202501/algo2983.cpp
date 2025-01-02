#include <bits/stdc++.h>
using namespace std;

// 周赛 378
class Solution {
public:
    vector<bool> canMakePalindromeQueries(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int half = n >> 1;
        string t = s.substr(half, half);
        reverse(t.begin(), t.end());
        s = s.substr(0, half);

        vector<vector<int>> pres_s;
        vector<vector<int>> pres_t;
        pres_s.assign(half+1, vector<int>(26));
        pres_t.assign(half+1, vector<int>(26));

        vector<int> pres_d(half+1);

        // 初始化 pres_s
        for (int i=0; i<half; i++) {
            for (int j= 0; j<26; j++) {
                pres_s[i+1][j] = pres_s[i][j] + (int(s[i]) == int('a') + j);
            }
        }

        // 初始化 pres_t
        for (int i=0; i<half; i++) {
            for (int j= 0; j<26; j++) {
                pres_t[i+1][j] = pres_t[i][j] + (int(t[i]) == int('a') + j);
            }
        }

        // 初始化 pres_d
        for (int i=0; i<half; i++) {
            pres_d[i+1] = pres_d[i] + (s[i]!=t[i]);
        }

        auto count = [&](int l, int r, vector<vector<int>>& pre) -> vector<int> {
            vector<int> res(26);
            for (int i=0; i<26; i++) {
                res[i] = pre[r+1][i] - pre[l][i];
            }
            return res;
        };

        auto substract = [&](vector<int> s1, vector<int> s2) -> vector<int> {
            for (int i=0; i<s1.size(); i++) {
                s1[i] -= s2[i];
                if (s1[i] < 0) return {};
            }
            return s1;
        };
        
        auto check = [&](int l1, int r1, int l2, int r2, vector<vector<int>>& pre1, vector<vector<int>>& pre2) {

            if (pres_d[l1] > 0 || pres_d[half] - pres_d[max(r1, r2)+1] > 0)
                return false;
            if (r2 <= r1) { // 区间包含
                return count(l1,r1,pre1) == count(l1, r1, pre2);
            } else if (r1 < l2) {
                return pres_d[l2] - pres_d[r1+1] == 0 &&
                    count(l1,r1,pre1) == count(l1, r1, pre2) &&
                    count(l2,r2,pre1) == count(l2, r2, pre2);
            } else {
                auto s1 = substract(count(l1,r1, pre1), count(l1,l2-1,pre2));
                auto s2 = substract(count(l2,r2, pre2), count(r1+1,r2,pre1));
                return !s1.empty() && !s2.empty() && s1 == s2;
            }
        };

        vector<bool> ans(queries.size());
        for (int i=0; i<queries.size(); i++) {
            auto &q = queries[i];
            int l1 = q[0], r1 = q[1], l2 = n - q[3] -1, r2 = n-q[2] - 1;
            if (l1<=l2) {
                ans[i] = check(l1,r1,l2,r2, pres_s, pres_t);
            } else{
                ans[i] = check(l2,r2,l1,r1,pres_t, pres_s);
            }

        }

        return ans; 
    }
};

int main() {
    Solution solution;
    vector<vector<int>> queries = {{1,1,3,5},{0,2,5,5}};
    vector<bool> result = solution.canMakePalindromeQueries("abcabc", queries);
    cout << "[";
    cout << boolalpha; // Enable boolalpha
    for (const bool& expr : result) {
        cout << expr << ", ";
    }
    cout << "]" << endl;
    return 0;
}