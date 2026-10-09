#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string maximumXor(string s, string t) {
        int cnt0 = 0, cnt1 = 0;
        for (auto & ch : t) 
            if (ch == '0') cnt0 ++;
            else cnt1 ++;
        
        string ans = "";
        for (auto & ch : s) {
            if (ch == '0') {
                if (cnt1) {ans += "1"; cnt1--; }
                else {ans += "0", cnt0 --;};
            } else {
                if (cnt0) {ans += "1"; cnt0--; }
                else {ans += "0", cnt1 --;};
            }
        }
        return ans;
    }

    string maximumXor2(string s, string t) {
        int cnt[2];
        for (auto & ch : t) cnt[ch-'0'] ++;
            
        string ans = "";
        for (auto & ch : s) {
            if (cnt[1^(ch-'0')]) {ans += "1"; cnt[1^(ch-'0')]--;}
            else {ans += "0"; cnt[ch-'0']--;}
        }
        return ans;
    }


};