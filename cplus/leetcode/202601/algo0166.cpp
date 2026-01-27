#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.8 其他
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        string sign = "";
        long long a = numerator, b = denominator;
        if (1LL * a * b < 0) sign = "-";
        a = abs(a); b = abs(b);
        long long intp = a / b;
        vector<int> fracs; unordered_map<long long, int> repeating;

        long long rem = a % b, rep_start = INT_MAX;
        while (rem) {
            int div = rem * 10 / b;
            rem = rem * 10 % b;
            long long mask = (1LL * div) << 32 | rem;
            if (repeating.count(mask)) {
                rep_start = repeating[mask]; break;
            } else {
                repeating[mask] = fracs.size(); fracs.push_back(div);
            }
        }

        string ans = to_string(intp);
        if (fracs.size()) {
            ans.push_back('.');
            for (int i=0; i<min((int)fracs.size(), (int)rep_start); i++) {
                ans.push_back('0' + fracs[i]);
            }
            if (rep_start < fracs.size()) {
                ans.push_back('(');
                for (int i=rep_start; i<fracs.size(); i++) {
                    ans.push_back('0' + fracs[i]);
                }
                ans.push_back(')');
            }
        }

        return sign + ans;   
    }
};