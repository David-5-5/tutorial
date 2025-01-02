#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 回文串贪心
class Solution {
public:
    bool checkPalindromeFormation(string a, string b) {
        int m = a.size(), n = a.size() / 2;

        auto sub_check = [&](string sub) {
            // cout << sub << endl;
            int l = sub.size();
            for (int i=0; i<l/2; i++)
                if (sub[i] != sub[l-i-1]) return false;
            return true;
        };

        auto check = [&] (string& str1, string& str2) {
            for (int i=0; i<n; i++) 
                if (str1[i] != str2[m-i-1])
                    return sub_check(str1.substr(i, m-i*2)) || 
                        sub_check(str2.substr(i,m-i*2)); 
            return true;
        };

        if (check(a,b) || check(b,a)) return true;

        return false;
    }
};