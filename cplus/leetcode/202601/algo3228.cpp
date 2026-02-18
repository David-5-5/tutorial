#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.4 从最左/最右开始贪心
class Solution {
public:
    int maxOperations(string s) {
        // 自行解答，从左开始贪心
        int ones = 0, ans = 0, n = s.length();
        bool shift = false;
        for (int i = 0; i<n; ++i) {
            if (s[i] == '1') {
                if (shift) {ans += ones; shift = false;}
                ones ++;
            } else if (ones) shift = true;
        }
        if (shift) ans += ones;
        return ans;  
    }

    int maxOperations2(string s) {
        s.push_back('1');   // 哨兵
        int ones = 0, ans = 0, n = s.length(); 
        bool shift = false;
        for (int i = 0; i<n; ++i) {
            if (s[i] == '1') {
                if (shift) {ans += ones; shift = false;}
                ones ++;
            } else if (ones) shift = true;
        }
        return ans;        
    }    
};