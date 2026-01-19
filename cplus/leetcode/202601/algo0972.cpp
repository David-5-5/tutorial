#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.8 其他
class Solution {
public:
    bool isRationalEqual(string s, string t) {
        // 自行解答 小学数学 循环小数转分数
        auto to_fraction = [] (string dec) -> tuple<int, int, int> {
            auto dot = dec.find('.');
            if (dot == string::npos) return {stoi(dec), 0, 1};

            int intpart = stoi(dec.substr(0, dot));
            int num = 0, den = 1;

            int par = dec.find('(');
            if (par == string::npos) {
                if (dot+1 < dec.length()) {
                    num = stoi(dec.substr(dot+1, dec.length()-dot-1));
                    den = pow(10, dec.length()-dot-1);
                    int g = gcd(num, den);
                    num /= g; den /= g;
                }
            } else {
                int norep = 0; if (dot+1 < par) norep = stoi(dec.substr(dot+1, par-dot-1));
                int rep = stoi(dec.substr(par+1, dec.length()-par-2));
                num = pow(10, dec.length()-par-2) * norep + rep - norep;
                
                den = pow(10, dec.length()-par-2) - 1;
                for (int _=0; _<par-dot-1; ++_) den *= 10;
                int g = gcd(num, den);
                num /= g; den /= g;
                if (num == den) {
                    intpart += 1; num = 0; den = 1;
                }
            }
            return {intpart, num, den};
        };
        tuple<int, int, int> s_val = to_fraction(s);
        tuple<int, int, int> t_val = to_fraction(t);
        

        return s_val == t_val;
    }
};