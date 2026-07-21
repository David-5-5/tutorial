#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int compress(vector<char>& chars) {
        int ans = 0, cnt = 1, i = 0, n = chars.size();
        while (i<n) {
            while (i+1 < n && chars[i] == chars[i+1]) {
                cnt ++; i++;
            }
            chars[ans ++] = chars[i];
            if (cnt > 1) {
                auto len = to_string(cnt);
                for (auto ch : len) chars[ans ++] = ch;
            }
            cnt = 1; i ++;
        }
        return ans;    
    }
};