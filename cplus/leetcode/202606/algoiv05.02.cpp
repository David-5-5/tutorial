#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string printBin(double num) {
        string ans = "0.";

        double a = 0.5;            
        for (int _=0; _<30 && num > 0; _++) {
            if (num - a >=0) {
                num -= a; ans.push_back('1');
            } else {
                ans.push_back('0');
            }
            a *= 0.5;
        }
        
        if (num == 0.0) return ans;
        else return "ERROR";

    }

    string printBin(double num) {
        string ans = "0.";
        double const epl = 1e-12;   // 带精度
        double a = 0.5;            
        for (int _=0; _<30 && num > epl; _++) {
            if (num >= a) {
                num -= a; ans.push_back('1');
            } else {
                ans.push_back('0');
            }
            a *= 0.5;
        }
        
        if (num < epl) return ans;
        else return "ERROR";
    }    
};