#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.4 组合型回溯
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        // 自行解答，感觉很别扭的实现
        vector<int> par_inx; int n = s.length();
        for (int i=0; i<n; ++i) if (s[i] == '(' || s[i] == ')') 
            par_inx.push_back(i);
        int m = par_inx.size(); 

        auto check = [&](int mask) -> bool {
            int left = 0;
            for (int i=0; i<m; ++i) {
                if ((mask >> i) & 1) {
                    if (s[par_inx[i]] == '(') left ++;
                    else left --;
                }
                if (left<0) return false;
            }
            return left == 0;
        };

        auto get_val = [&](int mask) {
            int par_ptr = 0; string res = "";
            for (int i=0; i<n; ++i) {
                if (s[i] != '(' && s[i] != ')') {
                    res += s[i];
                } else {
                    if ((mask>>par_ptr) & 1) {
                        res += s[i];
                    }
                    par_ptr ++;
                }
            }
            return res;
        };

        set<string> ans; int mx = 0;
        for (int mask = 0; mask<(1<<m); ++mask) {
            int len = __builtin_popcount(mask);
            if (len>=mx) {
                if (check(mask)) {
                    if (len > mx) {ans.clear(); mx=len;}
                    ans.insert(get_val(mask));
                }
            }
        }

        vector<string> vec_from_set(ans.begin(), ans.end());
        return  vec_from_set;
    }
};